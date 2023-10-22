#ifndef __AST_HPP__
#define __AST_HPP__

#include <iostream>
#include <vector>
#include <map>
#include "ast.cpp"


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
class AbstractType : public AST
{
  public:

};

// TODO
class FuncDef : public LocalDef
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
    If(Condition *c, Stmt *s1, Stmt *s2 = nullptr);
    void execute() const override;
  
  private:
    Condition *cond;
    Stmt      *stmt1;
    Stmt      *stmt2;
};

/* A vector of statements */ 
class Block : public Stmt
{
  public:
    Block();
    void execute() const override;
  
  private:
    std::vector<Stmt *> stmt_list;
};

//TODO
class Assign : public Stmt 
{
  public:
    Assign();
    void execute() const override;

};

class While : public Stmt 
{
  public:
    While();
    void execute() const override;
  
  private:
    Condition *cond;
    Block *block;
};

class Return : public Stmt
{
  public:
    Return();
    void execute() const override;
};

// TODO
class FuncCallStmt : public Stmt
{
  public:
    FuncCallStmt();
    void execute() const override;
};

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
    IntConst();
    int eval() const override;
  
  private:
    const int val; 
};


class CharConst : public Expr 
{
  public:
    CharConst();
    int eval() const override;
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

#endif
