#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <vector>
#include <map>
#include <string>


#define INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE -1


// TODO: Move this to the correct file, probably symbol.hpp
enum DATA_TYPE { DATA_TYPE_int, DATA_TYPE_char, DATA_TYPE_nothing };


class AST
{
  public:
    virtual void printAST(std::ostream &out) const = 0;
};

inline std::ostream &operator<<(std::ostream &out, const AST &ast)
{
  ast.printAST(out);
  return out;
}

/* abstract class */
class Stmt : public AST
{
  public:
    virtual void execute() const = 0;
};

/* abstract class */
class Expr : public AST
{
  public:
    virtual int eval() const = 0;

};

/* abstract class */
class LocalDef : public AST
{
  public:

};

/* abstract class */
class Condition : public Expr
{
  public:

};

/* abstract class */
class AbstractLvalue : public Expr
{
  public:

};



class If : public Stmt
{
  public:
    If(Condition *c, Stmt *s1, Stmt *s2 = nullptr) : cond(c),  stmt1(s1), stmt2(s2) {}
    
    void execute() const override {
      if (cond->eval())
        stmt1->execute();
      else if (stmt2 != nullptr)
        stmt2->execute();
    };

    void printAST(std::ostream &out) const override {
      out << "If(" << *cond << ", " << *stmt1;
      if (stmt2 != nullptr) out << ", " << *stmt2;
      out << ")";
    }

  private:
    Condition *cond;
    Stmt      *stmt1;
    Stmt      *stmt2;
};

/* A vector of statements */ 
class Block : public Stmt
{
  public:
    Block() {}
    
    void execute() const override {
      for (Stmt *s : stmt_list)
        s->execute();
    }

    void append(Stmt *s) { stmt_list.push_back(s); }

    void printAST(std::ostream &out) const override {
      out << "Block(";
      bool first = true;
      for (const auto &s : stmt_list) {
        if (!first) out << ", ";
        first = false;
        out << *s;
      }
      out << ")";
    }

  private:
    std::vector<Stmt *> stmt_list;
};

//TODO
class Assign : public Stmt 
{
  public:
    Assign(AbstractLvalue *l, Expr *e) : lval(l), expr(e) {}
    void execute() const override {
      // TODO
      // Update the valaue of lval to e->eval()
      // variables[*lval->Getval]  = e->eval()
    };

    void printAST(std::ostream &out) const override {
      out << *lval << " <- " << *expr;
    }
  
  private:
    AbstractLvalue *lval;
    Expr *expr;

};

class While : public Stmt 
{
  public:
    While(Condition *c, Stmt *s) : cond(c), stmt(s) {}
    
    void execute() const override {
      while(cond->eval())
        stmt->execute();
    };
  
    void printAST(std::ostream &out) const override {
      out << "While(" << *cond << "," << *stmt << ")";
    }

  private:
    Condition *cond;
    Stmt *stmt;
};

// TODO
class Return : public Stmt
{
  public:
    Return(Expr *e = nullptr) : expr(e) {}
    void execute() const override {}

    void printAST(std::ostream &out) const override {
      out << "Return(";
      if (expr != nullptr)
        out << *expr;
      out << ")";
    }

  private:
    Expr *expr;
};



class Id : public AbstractLvalue
{
  public:
    Id(std::string s) : str(s) {}
    // TODO
    int eval() const override {
      return 0;
    }
  
    void printAST(std::ostream &out) const override {
      out << "Id: " << str;
    }

  private:
    std::string str;
};


class StrLit : public AbstractLvalue
{
  public:
    StrLit(std::string *s) : str(s) {}
    // TODO
    // std::string eval() const override {
    //   return *str;
    // }
    // Just for compilation, replace with template
    int eval() const override {
      return 1;
    }

    void printAST(std::ostream &out) const override {
      out << "StrLit(" << *str <<  ")";
    }

  private:
    std::string *str;
};


class LMatrix : public AbstractLvalue
{
  public:
    LMatrix(AbstractLvalue *lval, Expr *e) : lvalue(lval), expr(e) {}
    // TODO
    int eval() const override {
      return 0;
    }

    void printAST(std::ostream &out) const override {
      out << *lvalue;
      out << "[";
      out << *expr;
      out << "]";  
    }

  private:
    AbstractLvalue *lvalue;
    Expr *expr;
};

// TODO
/* In situations like a <- f(); the rhs has to implement eval() */ 
class FuncCall : public Expr 
{
  public:
    FuncCall(Id *f, std::vector<Expr *> *par) : funcName(f), parametersExprList(par) {}
    int eval() const override {
      return 0;
    }

    void printAST(std::ostream &out) const override {
      bool first = true;
      out << "FuncCall(" << *funcName;
      if (!(parametersExprList->empty())) {
        out << "[";
        for (auto exprPtr : *parametersExprList) {
          if (!first)
            out << ",";
          first = false;
          out << *exprPtr;
        }
        out << "]";
      }
      out << ")";
    }

  private:
    Id *funcName;
    std::vector<Expr *> *parametersExprList;
};


/* For example f(); */
class FuncCallStmt : public Stmt
{
  public:
    FuncCallStmt(FuncCall *fc) : func(fc) {}
    void execute() const override {
      func->eval(); 
    }
  
    void printAST(std::ostream &out) const override {
      out << "FuncCallStmt(" << *func << ")";
    }

  private:
    FuncCall* func;
};



class IntConst : public Expr 
{
  public:
    IntConst(int v) : val(v) {}
    
    int eval() const override {
      return val;
    }

    void printAST(std::ostream &out) const override {
      out << "IntConst(" << val << ")";
    }
  
  private:
    const int val; 
};


class CharConst : public Expr 
{
  public:
    CharConst(char c) : val(c) {}
    
    int eval() const override {
      return val;
    }
  
    void printAST(std::ostream &out) const override {
      out << "CharConst(" << val << ")";
    }
    
    private:
      char val;
};


class BinOp : public Expr 
{
  public:
    BinOp(Expr *l, char o, Expr *r): left(l), op(o), right(r) {}
  
    virtual int eval() const override {
      switch (op) {
        case '+': return left->eval() + right->eval();
        case '-': return left->eval() - right->eval();
        case '*': return left->eval() * right->eval();
        case '/': return left->eval() / right->eval();
        case '%': return left->eval() % right->eval();
      }
      return 0; /* This will never be reached */
    }

    void printAST(std::ostream &out) const override {
      out << op << "(" << *left << ", " << *right << ")";
    }

  private:
    Expr *left;
    char op;
    Expr *right;

};


class UnaryOp : public Expr 
{
  public:
    UnaryOp(char o, Expr *e) : expr(e), op(o) {}
    int eval() const override {
      if (op == '+')
        return expr->eval();
      if (op == '-')
        return -1*expr->eval();
      
      exit(1);  /* This should never be reached */
      return 0; 
    }
  
    void printAST(std::ostream &out) const override {
      out << op << "(" << *expr;
    }

  private:
    Expr *expr;
    char op;
};


class LogicalCond : public Condition
{
  public:
    LogicalCond(Condition *l, char o, Condition *r = nullptr): c1(l), op(o), c2(r) {}
    int eval() const override {
      // Take care of short-circuit
      switch (op) {
        case 'n': return !(c1->eval());
        case 'a': {
          if (c1->eval() != 1)
            return 0;
          return c2->eval();
        }
        case 'o': {
          if (c1->eval() == 1)
            return 1;
          return c2->eval();
        }
      }
      return 0; /* This will never be reached */
    }

    void printAST(std::ostream &out) const override {
      out << op << "(" << *c1;
      if (c2 != nullptr)
        out << ", " << *c2 << ")";
    }

  private:
    Condition *c1;
    char op;
    Condition *c2;
};


class NumericCond : public Condition
{
  public:
    NumericCond(Expr *l, char o, Expr *r) : left(l), op(o), right(r) {}
    int eval() const override {
      switch (op) {
        case '=': return (left->eval() == right->eval());
        case '#': return (left->eval() != right->eval());
        case '>': return (left->eval() > right->eval());
        case '<': return (left->eval() < right->eval());
        case 'l': return (left->eval() <= right->eval());
        case 'g': return (left->eval() >= right->eval());
      }
      return 0; /* This will never be reached */
    }

    void printAST(std::ostream &out) const override {
      out << op << "(" << *left << ", " << *right << ")";
    }

  private:
    Expr *left;
    char op;
    Expr *right;
};


class Type : public AST
{
  public:
    Type(DATA_TYPE t, std::vector<int> *dims_vec) : data_type(t), dims(dims_vec) {};
  
    void printAST(std::ostream &out) const override {
        out << "Type(";
        switch (data_type)
        {
        case DATA_TYPE_int:
          out << "int";
          break;
        case DATA_TYPE_char:
          out << "char";
          break;
        default:
          exit(1); /* Will never be reached */
          break;
        }
        if (dims != nullptr) {
          for (const auto &s : *dims) {
            out << "[";
            if (s != INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE) out << s; 
            out << "]";
          }
        }
        out << ")";
      }

  private:
    DATA_TYPE data_type;
    /*
    Possibilites for dims:
    - dims.size() == 0 : The type is a basic one meaning either int or char (not an arr)
    - dims[0] == INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE : The type is defined in a function definition without the first dimension eg fun reverse (ref s : char[])
    TODO: Make sure that the user can't somehow define the dimension to be equal to INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE eg fun reverse (ref s : char[-1]) should produce an error
    - In all other cases the dims vector holds the actual dimensions passed by the programmer
    */
    std::vector<int> *dims;

};


class VarDef : public LocalDef
{
  public:
    VarDef(std::vector<Id *> *ids_vec, Type *t ) : ids(ids_vec), type(t) {};

    void printAST(std::ostream &out) const override {
      out << "VarDef(";
      out << *type;
      out << "Ids: (";
      bool first = true;
      for (const auto &s : *ids) {
        if (!first) out << ", ";
        first = false;
        out << *s;
      }
      out << ")";
    }


  private:
    std::vector<Id *> *ids; // Will never be nullptr by construction of parser
    Type *type;
};







class FParDef : public AST
{
  public:
    FParDef(std::vector<Id *> *ids_vec, Type *f, bool b) : ids(ids_vec), fpar_type(f), ref(b) {};

    void printAST(std::ostream &out) const override {
      out << "FParDef(";
      if (ref) out << "ref:";
      out << "Ids(";
      bool first = true;
      for (const auto &s : *ids) {
        if (!first) out << ", ";
        first = false;
        out << *s;
      }
      out << ") : ";
      out << *fpar_type;
      out << ")";
    }

  private:
    std::vector<Id *> *ids;
    Type *fpar_type;
    bool ref;
};



class Header : public AST
{
  public:
    Header(Id *i, std::vector<FParDef *> *vec_defs, DATA_TYPE dt) : id(i), fpar_defs(vec_defs), ret_type(dt) {} ;

    void printAST(std::ostream &out) const override {
      out << "Header(";
      out << *id;
      out << "FParDefs(";
      bool first = true;
      for (const auto &s : *fpar_defs) {
        if (!first) out << ", ";
        first = false;
        out << *s;
      }
      
      out << ") : ";
      switch (ret_type)
      {
        case DATA_TYPE_int:
          out << "int";
          break;
        case DATA_TYPE_char:
          out << "char";
          break;
        case DATA_TYPE_nothing:
          out << "nothing";
          break;
        default:
          exit(1); /* Will never be reached */
          break;
      }
      out << ")";
    }

  private:
    Id *id;
    std::vector<FParDef *> *fpar_defs;
    DATA_TYPE ret_type;
};


class FuncDecl : public LocalDef
{
  public:
    FuncDecl(Header *h) : header(h) {};
    
    void printAST(std::ostream &out) const override {
      out << "FuncDecl(";
      out << *header;
      out << ")";
    }

  private:
    Header *header; 
};

// TODO
class FuncDef : public LocalDef
{
  public:
    FuncDef(Header *h,  std::vector<LocalDef *> *vector_def, Block *b) : header(h), local_defs(vector_def), block(b) {} ;
  
    void printAST(std::ostream &out) const override {
      out << "FuncDef(";
      out << *header;
      out << "LocalDefs(";
      bool first = true;
      for (const auto &s : *local_defs) {
        if (!first) out << ", ";
        first = false;
        out << *s;
      }
      out << ") : ";
      out << *block;
      out << ")";
    }

  private:
    Header *header;
    std::vector<LocalDef *> *local_defs;
    Block *block;
};


class Program : public AST
{
  public:
    Program(FuncDef *f) : fd(f) {}
  
    void printAST(std::ostream &out) const override {
      out << "Program(" << *fd << ")";
    }

  private:
    FuncDef *fd;
};

#endif