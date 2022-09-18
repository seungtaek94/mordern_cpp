# Interface Segregation Principle(ISP)
# 인터페이스 분리 원칙

```c++
struct MyPrinter : IMachine
{
    void print() override;
    void fax() override;
    void scan() override;
};
    
struct IMachine
{
    virtual void print() = 0;
    virtual void fax() = 0;
    virtual void scan() = 0;
};
```

위와 같은 프린터 인터페이스를 이용해 복합 기능을 하는 프린터를 만들었다고 가정하자, 위의 경우에서라면 문제가 없지다.
하지만 이후에 팩스 및 스캔 기능이 없는 프린터를 만들려고 하면 위의 인터페이스에서는 팩스와 스캔 기능을 만들도록 강제하기 때문에 빈 함수를 만들어 대응해야한다.

```c++
struct IPrinter
{
    virtual void print() = 0;
};

struct IScanner
{
   virtual void scan() = 0; 
};
```
ISP를 지키기 위해서는 위처럼 구현할 대상을 선별할 수 있도록 인터페이스를 별개로 두어야한다는 것이다.

```c++
struct Printer: IPrinter
{
    void print() override;
};

struct Scanner: IScanner
{
    void scan() override;
};
```
위처럼 인터페이스를 기능 별로 따로 구현한다면, 기능에 따라 프린터 및 스캐너를 따로 따로 구현할 수 있다.

```c++
struct IMachine: IPrinter, IScanner{};

struct Machine: IMachine
{
    IPrinter& printer;
    IScanner& scanner;
    
    Machine(IPrinter& printer, IScanner& scanner)
        : printer(printer), scanner(scanner){}
    
    void print() override {
        printer.print();
    }
    
    void scan() override {
        scanner.scan();
    }
};
```
위처럼 기능이 분리된 인터페이스를 이용해 프린트 및 스캔 기능이있는 복합기를 만들고 싶다면,
두 인터페이스를 상속하는 복합 인터페이스를 만들어 위처럼 구현하면 된다.
