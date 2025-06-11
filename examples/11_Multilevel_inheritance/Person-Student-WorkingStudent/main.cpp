#include <iostream>

using namespace std;

#include "WorkingStudent.hpp"
#include "Master.hpp"

int main()
{
    WorkingStudent st("Ivan Petrov", 43210, 1000);
    st.info();
    Person *h = &st;
    h->info();

    cout << "----------------------- \n";
    st.setName("Ivan Ivanov");
    st.info();
    cout << "----------------------- \n\n";

    Master master("AI", "Dragan", 21123);
    master.info();
    return 0;
}
