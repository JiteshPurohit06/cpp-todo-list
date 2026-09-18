#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <limits>

using namespace std;

struct todolist
{
    int id;
    string task;
};

int ID = 0;

void banner();
void addTask();
void showTask();
void searchTask();
void deleteTask();
void updateTask();
void loadID();
void pauseScreen();

int main()
{
    system("cls");

    loadID();

    while(true)
    {
        system("cls");
        banner();

        cout << "\n\t1. Add Task" << endl;
        cout << "\n\t2. Show Task" << endl;
        cout << "\n\t3. Search Task" << endl;
        cout << "\n\t4. Delete Task" << endl;
        cout << "\n\t5. Update Task" << endl;
        cout << "\n\t6. Exit" << endl;

        int choice;
cout << "\n\tEnter your choice: ";

if (!(cin >> choice))
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nInvalid input! Please enter a number." << endl;
    pauseScreen();
    continue;
}

        switch(choice)
        {
            case 1:
                addTask();
                break;

            case 2:
                showTask();
                break;

            case 3:
                searchTask();
                break;

            case 4:
                deleteTask();
                break;

            case 5:
                updateTask();
                break;

            case 6:
                cout << "\nExiting program..." << endl;
                return 0;

            default:
                cout << "\nInvalid choice. Please try again." << endl;
                pauseScreen();
                break;
        }
    }
}

void banner()
{
    cout << "==============================" << endl;
    cout << "\t|       TO DO LIST         |" << endl;
    cout << "==============================" << endl;
}

void pauseScreen()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void loadID()
{
    ifstream fin;
    fin.open("todo.txt");

    if(!fin)
    {
        return;
    }

    todolist todo;

    while(fin >> todo.id)
    {
        fin.ignore();
        getline(fin, todo.task);

        if(todo.id > ID)
        {
            ID = todo.id;
        }
    }

    fin.close();
}

void addTask()
{
    system("cls");
    banner();

    todolist todo;

    cout << "\nEnter new task: ";
    cin.ignore();
    getline(cin, todo.task);

    char save;
    cout << "Do you want to save this task? (y/n): ";
    cin >> save;

    if(save == 'y' || save == 'Y')
    {
        ID++;

        ofstream fout;
        fout.open("todo.txt", ios::app);

        fout << ID << endl;
        fout << todo.task << endl;

        fout.close();

        cout << "\nTask saved successfully!" << endl;

        char more;
        cout << "Do you want to add another task? (y/n): ";
        cin >> more;

        if(more == 'y' || more == 'Y')
        {
            addTask();
        }
        else
        {
            pauseScreen();
        }
    }
    else
    {
        cout << "\nTask not saved." << endl;
        pauseScreen();
    }
}

void showTask()
{
    system("cls");
    banner();

    ifstream fin;
    fin.open("todo.txt");

    if(!fin)
    {
        cout << "\nNo tasks found." << endl;
        pauseScreen();
        return;
    }

    todolist todo;
    bool found = false;

    while(fin >> todo.id)
    {
        fin.ignore();
        getline(fin, todo.task);

        cout << "\nID: " << todo.id << endl;
        cout << "Task: " << todo.task << endl;
        cout << "------------------------" << endl;

        found = true;
    }

    fin.close();

    if(!found)
    {
        cout << "\nNo tasks found." << endl;
    }

    pauseScreen();
}

void searchTask()
{
    system("cls");
    banner();

    int searchId;

    cout << "\nEnter the ID of the task to search: ";
    cin >> searchId;

    ifstream fin;
    fin.open("todo.txt");

    if(!fin)
    {
        cout << "\nNo tasks found." << endl;
        pauseScreen();
        return;
    }

    todolist todo;
    bool found = false;

    while(fin >> todo.id)
    {
        fin.ignore();
        getline(fin, todo.task);

        if(todo.id == searchId)
        {
            cout << "\nID: " << todo.id << endl;
            cout << "Task: " << todo.task << endl;

            found = true;
            break;
        }
    }

    fin.close();

    if(!found)
    {
        cout << "\nTask with ID " << searchId << " not found." << endl;
    }

    pauseScreen();
}

void deleteTask()
{
    system("cls");
    banner();

    int deleteId;

    cout << "\nEnter the ID of the task to delete: ";
    cin >> deleteId;

    ifstream fin;
    fin.open("todo.txt");

    if(!fin)
    {
        cout << "\nNo tasks found." << endl;
        pauseScreen();
        return;
    }

    ofstream fout;
    fout.open("temp.txt");

    todolist todo;
    bool found = false;

    while(fin >> todo.id)
    {
        fin.ignore();
        getline(fin, todo.task);

        if(todo.id != deleteId)
        {
            fout << todo.id << endl;
            fout << todo.task << endl;
        }
        else
        {
            found = true;
        }
    }

    fin.close();
    fout.close();

    remove("todo.txt");
    rename("temp.txt", "todo.txt");

    if(found)
    {
        cout << "\nTask with ID " << deleteId
             << " deleted successfully." << endl;
    }
    else
    {
        cout << "\nTask with ID " << deleteId
             << " not found." << endl;
    }

    pauseScreen();
}

void updateTask()
{
    system("cls");
    banner();

    int updateId;

    cout << "\nEnter the ID of the task to update: ";
    cin >> updateId;

    ifstream fin;
    fin.open("todo.txt");

    if(!fin)
    {
        cout << "\nNo tasks found." << endl;
        pauseScreen();
        return;
    }

    ofstream fout;
    fout.open("temp.txt");

    todolist todo;
    bool found = false;

    while(fin >> todo.id)
    {
        fin.ignore();
        getline(fin, todo.task);

        if(todo.id == updateId)
        {
            cout << "\nCurrent Task: " << todo.task << endl;

            cout << "Enter new task: ";
            cin.ignore();
            getline(cin, todo.task);

            found = true;
        }

        fout << todo.id << endl;
        fout << todo.task << endl;
    }

    fin.close();
    fout.close();

    remove("todo.txt");
    rename("temp.txt", "todo.txt");

    if(found)
    {
        cout << "\nTask with ID " << updateId
             << " updated successfully." << endl;
    }
    else
    {
        cout << "\nTask with ID " << updateId
             << " not found." << endl;
    }

    pauseScreen();
}