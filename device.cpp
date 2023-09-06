#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
int streamcounter;

class Stream
{
    private:
      double mass_flow;
      string name;
    public:
      Stream(int s){setName("s"+std::to_string(s));}
      void setName(string s){name=s;}
      string getName(){return name;}
      void setMassFlow(double m){mass_flow=m;}
      double getMassFlow(){return mass_flow;}
      void print(){cout<<"Stream "<<getName()<<" flow = "<<getMassFlow()<<endl;}
};

class Device
{
    protected:
      vector<shared_ptr<Stream>> inputs;
      vector<shared_ptr<Stream>> outputs;
    public:
      void addInput(shared_ptr<Stream> s){inputs.push_back(s);}
      void addOutput(shared_ptr<Stream> s){outputs.push_back(s);}
      virtual void updateOutputs() = 0;
};

class SimpleColumn : public Device
{
public:
    SimpleColumn() {}  // Конструктор

    // Метод для обновления выходных потоков на основе входного потока
    void updateOutputs() override {
        if (inputs.size() == 1 && outputs.size() == 2) {
            // Получаем массовый расход входного потока
            double inputMassFlow = inputs[0]->getMassFlow();

            // Простой пример: делим входной поток поровну на два выходных потока
            double outputMassFlow = inputMassFlow / 2.0;

            // Устанавливаем массовый расход для обоих выходных потоков
            outputs[0]->setMassFlow(outputMassFlow);
            outputs[1]->setMassFlow(outputMassFlow);
        }
    }
};

int main()
{
    streamcounter = 0;

    shared_ptr<Stream> s1(new Stream(++streamcounter));
    shared_ptr<Stream> s2(new Stream(++streamcounter));
    shared_ptr<Stream> s3(new Stream(++streamcounter));
    s1->setMassFlow(10.0);
    s2->setMassFlow(5.0);

    SimpleColumn column;

    // Добавляем потоки в колонну
    column.addInput(s1);
    column.addOutput(s2);
    column.addOutput(s3);

    // Обновляем выходные потоки
    column.updateOutputs();

    // Выводим информацию о потоках
    s1->print();
    s2->print();
    s3->print();

    return 0;
}
