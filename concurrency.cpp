#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int consumed1, consumed2, consumed3 = 0;
int servedAmount = 0;
bool chefAwake = true;
int randFood1 = 0;
int randFood2 = 0;
char const *food[] = {"Hamburger", "Fries", "Soda"};


void *chef(void *arg)
{
    srand(static_cast<unsigned int>(time(NULL)));
    while(servedAmount != 100)
    {
        if (chefAwake == true)
        {
            randFood1 = rand() % 3;
            randFood2 = rand() % 3;
            
            // no 2 same foods made together
            while(randFood1 == randFood2)
            {
                randFood2 = rand() % 3;
            }
            cout << food[randFood1] << " and " << food[randFood2] << endl;;
            chefAwake = false;
            servedAmount++;
        }
    }
    sleep(1);
    cout << "Final Stats of Amount of Times Eaten by 3 Customers: " << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Customer 1: " << consumed1 << endl;
    cout << "Customer 2: " << consumed2 << endl;
    cout << "Customer 3: " << consumed3 << endl;
    cout << endl;
    exit(0);
}


void *customer(void *arg)
{
    while(1)
    {
        if (!chefAwake && randFood1 != (long)arg && randFood2 != (long)arg)
        {
            cout << "Customer eating: " << (long)arg + 1 << endl;
            cout << endl;
            if ((long)arg == 0)
            {
                consumed1++;
            }
            else if ((long)arg == 1)
            {
                consumed2++;
            }
            else if ((long)arg == 2)
            {
                consumed3++;
            }
            chefAwake = true;
        }
    }
}

int main()
{
    cout << "3 Customers are Eating" << endl;
    cout << "------------------------" << endl;
    pthread_t customer1ID,customer2ID,customer3ID,chefID;
    
    //pthread_create(&ID, &attr, function pointer, args);
    pthread_create(&chefID, 0, chef, 0);
    pthread_create(&customer1ID, 0, customer, (void*)0);
    pthread_create(&customer2ID, 0, customer, (void*)1);
    pthread_create(&customer3ID, 0, customer, (void*)2);
    
    while(1);
}
