#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

// ANSI escape codes for text color
#define ANSI_RESET   "\033[0m"
#define ANSI_RED     "\033[1;31m"
#define ANSI_GREEN   "\033[1;32m"
#define ANSI_YELLOW  "\033[1;33m"
#define ANSI_BLUE    "\033[1;34m"

using namespace std;

class Task {
public:
    int id;
    string description;
    bool completed;

    Task(int id, string description, bool completed = false) 
        : id(id), description(move(description)), completed(completed) {}
};

class TaskManager {
private:
    vector<Task> tasks;
    int next_id;

public:
    TaskManager() : next_id(1) {}

    void saveTasks(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.id << '|' << task.description << '|' << task.completed << '\n';
            }
            file.close();
        } else {
            cout << ANSI_RED << "Unable to save tasks to file." << ANSI_RESET << endl;
        }
    }

    void loadTasks(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            tasks.clear();
            Task task(0, "");
            char pipe;
            while (file >> task.id >> pipe >> ws && getline(file, task.description, '|') && file >> task.completed) {
                tasks.push_back(task);
                next_id = max(next_id, task.id + 1);
            }
            file.close();
        } else {
            cout << ANSI_YELLOW << "No existing tasks found." << ANSI_RESET << endl;
        }
    }

    void listTasks() {
        if (tasks.empty()) {
            cout << ANSI_YELLOW << "No tasks available." << ANSI_RESET << endl;
        } else {
            cout << ANSI_BLUE << "To-Do List:" << ANSI_RESET << endl;
            for (const auto& task : tasks) {
                if (task.completed) {
                    cout << ANSI_GREEN << task.id << ". [x] " << task.description << ANSI_RESET << endl;
                } else {
                    cout << ANSI_RED << task.id << ". [ ] " << task.description << ANSI_RESET << endl;
                }
            }
        }
    }

    void addTask() {
        cout << "Enter task description: ";
        string description;
        getline(cin, description);
        tasks.push_back(Task(next_id++, description));
    }

    void editTask() {
        cout << "Enter task ID to edit: ";
        int id;
        cin >> id;
        cin.ignore();
        auto it = find_if(tasks.begin(), tasks.end(), [id](const Task& task) { return task.id == id; });
        if (it != tasks.end()) {
            cout << "Enter new description: ";
            getline(cin, it->description);
        } else {
            cout << ANSI_YELLOW << "Task ID not found." << ANSI_RESET << endl;
        }
    }

    void markTaskCompleted() {
        cout << "Enter task ID to mark as completed: ";
        int id;
        cin >> id;
        auto it = find_if(tasks.begin(), tasks.end(), [id](const Task& task) { return task.id == id; });
        if (it != tasks.end()) {
            it->completed = true;
        } else {
            cout << ANSI_YELLOW << "Task ID not found." << ANSI_RESET << endl;
        }
    }

    void deleteTask() {
        cout << "Enter task ID to delete: ";
        int id;
        cin >> id;
        auto it = remove_if(tasks.begin(), tasks.end(), [id](const Task& task) { return task.id == id; });
        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
        } else {
            cout << ANSI_YELLOW << "Task ID not found." << ANSI_RESET << endl;
        }
    }
};

void credits() {
    
    cout << endl;
    cout << "*****************************" << endl;
    cout << "*        CREDITS            *" << endl;
    cout << "*****************************" << endl;
    cout << ANSI_BLUE << "This program was created as a project in Computer Programming 2 for the BS in Computer Science Program at University of Science and Technology of Southern Philippines." << ANSI_RESET << endl;
    cout << endl;
    cout << ANSI_GREEN << "CS1C - Group 1 Members:" << ANSI_RESET << endl;
    cout << "- Sisi, Kent Jasper C." << endl;
    cout << "- Shane B. Pagara" << endl;
    cout << "- Mitch Dumdum" << endl;
    cout << "- Jealry Escolar Pulpul" << endl;
    cout << "- Sofia Belle Villarente" << endl;
    cout << "- Alyssa Euana" << endl;
    cout << "- Charles Sorongon" << endl;
    cout << "- Gerald Boniel" << endl;
    cout << "- Karl Matt Jurial" << endl;
    cout << "- Kyle Palongpalong" << endl;
    cout << "- Mark Bautista Usman" << endl;
    cout << "- Paul Saligumba" << endl;
    cout << "- Ruiz Sagosa" << endl;

}
int main() {
    TaskManager manager;
    manager.loadTasks("tasks.txt");
    cout << R"(


        _            _                             
        | |          | |                                  
        | |_ __ _ ___| | ___ __   __ ___      _____      
        | __/ _` / __| |/ / '_ \ / _` \ \ /\ / / __| 
        | || (_| \__ \   <| |_) | (_| |\ V  V /\__ \  
        \__\__,_|___/_|\_\ .__/ \__,_| \_/\_/ |___/  
                        | |                           
                        |_|                              
                                   

)";
    int choice;
    do {
        cout << endl;
        cout << ANSI_BLUE << "To-Do List Manager" << ANSI_RESET << endl;
        cout << "1. List Tasks" << endl;
        cout << "2. Add Task" << endl;
        cout << "3. Edit Task" << endl;
        cout << "4. Mark Task as Completed" << endl;
        cout << "5. Delete Task" << endl;
        cout << ANSI_GREEN << "6. Credits" << ANSI_RESET << endl;
        cout << "7. Save and Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                manager.listTasks();
                break;
            case 2:
                manager.addTask();
                break;
            case 3:
                manager.editTask();
                break;
            case 4:
                manager.markTaskCompleted();
                break;
            case 5:
                manager.deleteTask();
                break;
            case 6:
                credits();
                break;
            case 7:
                manager.saveTasks("tasks.txt");
                cout << ANSI_GREEN << "Tasks saved. Exiting..." << ANSI_RESET << endl;
                break;

            default:
                cout << ANSI_YELLOW << "Invalid choice. Please try again." << ANSI_RESET << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}
