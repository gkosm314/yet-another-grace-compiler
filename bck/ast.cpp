#include "ast.hpp"


// TODO
class FuncDef : public LocalDef
{
  public:
    
};


class If : public Stmt
{
  public:
    If(Condition *c, Stmt *s1, Stmt *s2 = nullptr) : cond(c),  stmt1(s1), stmt2(s2) {};
    
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
    Block() {};
    
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
    Assign(AbstractLvalue *l, Expr *e) : lval(l), expr(e) {};
    void execute() const override {
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
    While(Condition *c, Stmt *s) : cond(c), stmt(s) {};
    
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
    Return(Expr *e = nullptr) : expr(e) {};
    void execute() const override {};

    void printAST(std::ostream &out) const override {
      out << "Return(";
      if (expr != nullptr)
        out << *expr;
      out << ")";
    }

  private:
    Expr *expr;
};

// TODO
class FuncCallStmt : public Stmt
{
  public:
    FuncCallStmt(FuncCallExpression* fe) : funcexpr(fe) {};
    void execute() const override;
  
  private:
    FuncCallExpression* funcexpr;
};

// TODO
/* In situations like a = f(); the rhs has to implement eval() */ 
class FuncCallExpression : public Expr 
{
  public:
    FuncCallExpression();
    int eval() const override;
};

class IntConst : public Expr 
{
  public:
    IntConst(int v) : val(v) {};
    
    int eval() const override{
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
    CharConst(char c) : val(c) {};
    
    int eval() const override {
      return val;
    };
  
    void printAST(std::ostream &out) const override {
      out << "CharConst(" << val << ")";
    }
    
    private:
      char val;
};


class BinOp : public Expr 
{
  public:
    BinOp();
    int eval() const override;
};


class UnaryOp : public Expr 
{
  public:
    UnaryOp();
    int eval() const override;
};


class LogicalCond : public Condition
{
  public:
    LogicalCond();
    int eval() const override;
};


class NumericCond : public Condition
{
  public:
    NumericCond();
    int eval() const override;
};

class Id : AbstractLvalue
{
  public:
    Id();
    int eval() const override;
};


class StrLit : AbstractLvalue
{
  public:
    StrLit();
    int eval() const override;
};


class LMatrix : AbstractLvalue
{
  public:
    LMatrix();
    int eval() const override;
};


class Type : public AbstractType
{
  public:
    Type();

};


class RetType : public AbstractType
{
  public:
    RetType();

};


class FParType : public AbstractType
{
  public:
    FParType();

};


class VarDef : public LocalDef
{
  public:
    VarDef();
};


class FuncDecl : public LocalDef
{
  public:
    FuncDecl();
};


class Program : public FuncDef
{
  public:
    Program();
};


class FParDef : public AST
{
  public:
    FParDef();
};


class Header : public AST
{
  public:
    Header();
};
