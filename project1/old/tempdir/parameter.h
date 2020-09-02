#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>
#include <iostream>
class Parameter
{
    public:
    Parameter(){}
    Parameter(std::string name, double initval, double stepsize) { m_name = name; m_value=initval; m_step=stepsize;}
    //get
    std::string getName() {return m_name;}
    double getValue() {return m_value; }
    double getStep() {return m_step; }
    //set
    void setName(std::string name) { m_name = name; }
    void setValue(double value) { m_value = value; }
    void setStep(double step) {m_step = step;}
    
    void step() { m_value += m_step; }
    void step(double step) {m_value += step;}//std::cout<<"step: "<<step<<std::endl;}
    
    private:
    std::string m_name = "alpha";
    double m_value = 0.3;
    double m_step = 0.05;
};

#endif//PARAMETER_H
