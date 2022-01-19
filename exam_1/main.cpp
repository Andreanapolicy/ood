#include <memory>
#include <iostream>

using namespace std;

struct Add;
struct Sub;
struct Const;

struct IVisitor
{
	virtual void visitAdd(Add& addStructure) = 0;

    virtual void visitSub(Sub& addStructure) = 0;

    virtual void visitConst(Const& addStructure) = 0;
};

struct Expr
{
	virtual ~Expr() = default;
    virtual void Accept(IVisitor& visitor) = 0;
};

struct Add : Expr
{
    Add(unique_ptr<Expr> lhsUniquePtr, unique_ptr<Expr> rhsUniquePtr)
    {
        lhs = move(lhsUniquePtr);
        rhs = move(rhsUniquePtr);
    }

    unique_ptr<Expr> lhs;
	unique_ptr<Expr> rhs;

	void Accept(IVisitor& visitor) override
	{
        visitor.visitAdd(*this);
	}
};

struct Sub : Expr
{
    Sub(unique_ptr<Expr> lhsUniquePtr, unique_ptr<Expr> rhsUniquePtr)
    {
        lhs = move(lhsUniquePtr);
        rhs = move(rhsUniquePtr);
    }

	unique_ptr<Expr> lhs;
	unique_ptr<Expr> rhs;

    void Accept(IVisitor& visitor) override
    {
        visitor.visitSub(*this);
    }
};

struct Const : Expr
{
    int value;

    explicit Const(int startValue)
    {
        value = startValue;
    }

    void Accept(IVisitor& visitor) override
    {
        visitor.visitConst(*this);
    }
};

struct CalculatorVisitor: IVisitor
{
    void visitAdd(Add& addStructure) override
    {
        auto newCalculatorVisitorForLHS = CalculatorVisitor();
        auto newCalculatorVisitorForRHS = CalculatorVisitor();

        addStructure.lhs->Accept(newCalculatorVisitorForLHS);
        const int firstValue = newCalculatorVisitorForLHS.GetValue();

        addStructure.rhs->Accept(newCalculatorVisitorForRHS);
        const int secondValue = newCalculatorVisitorForRHS.GetValue();

        value = firstValue + secondValue;
    }

    void visitSub(Sub& subStructure) override
    {
        auto newCalculatorVisitorForLHS = CalculatorVisitor();
        auto newCalculatorVisitorForRHS = CalculatorVisitor();

        subStructure.lhs->Accept(newCalculatorVisitorForLHS);
        const int firstValue = newCalculatorVisitorForLHS.GetValue();

        subStructure.rhs->Accept(newCalculatorVisitorForRHS);
        const int secondValue = newCalculatorVisitorForRHS.GetValue();

        value = firstValue - secondValue;
    }

    void visitConst(Const& constStructure) override
    {
        value = constStructure.value;
    }

    int GetValue() const
    {
        return value;
    }

private:
    int value = 0;
};

struct OutputVisitor: IVisitor
{
    void visitAdd(Add& addStructure) override
    {
        cout << "(";
        addStructure.lhs->Accept(*this);
        cout << " + ";
        addStructure.rhs->Accept(*this);
        cout << ")";
    }

    void visitSub(Sub& subStructure) override
    {
        cout << "(";
        subStructure.lhs->Accept(*this);
        cout << " - ";
        subStructure.rhs->Accept(*this);
        cout << ")";
    }

    void visitConst(Const& constStructure) override
    {
        cout << constStructure.value;
    }
};

int main()
{
    auto* calculatorVisitor = new CalculatorVisitor;
    IVisitor* outputVisitor = new OutputVisitor;
	auto x = make_unique<Const>(3);
	auto y = make_unique<Const>(4);
	auto xPlusY = make_unique<Add>(move(x), move(y));
	auto z = make_unique<Const>(2);
	auto xPlusYMinusZ = make_unique<Sub>(move(xPlusY), move(z));

    xPlusYMinusZ->Accept(*calculatorVisitor);

	int result = calculatorVisitor->GetValue();

    xPlusYMinusZ->Accept(*outputVisitor);
    cout << endl;
    cout << result;
}