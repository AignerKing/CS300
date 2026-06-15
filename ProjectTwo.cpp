#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course aCourse) {
        course = aCourse;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
            inOrder(node->right);
        }
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void Insert(Course course) {
        Node* newNode = new Node(course);

        if (root == nullptr) {
            root = newNode;
        }
        else {
            Node* current = root;

            while (current != nullptr) {
                if (course.courseNumber < current->course.courseNumber) {
                    if (current->left == nullptr) {
                        current->left = newNode;
                        current = nullptr;
                    }
                    else {
                        current = current->left;
                    }
                }
                else {
                    if (current->right == nullptr) {
                        current->right = newNode;
                        current = nullptr;
                    }
                    else {
                        current = current->right;
                    }
                }
            }
        }
    }

    void InOrder() {
        inOrder(root);
    }

    Course Search(string courseNumber) {
        Node* current = root;

        while (current != nullptr) {
            if (current->course.courseNumber == courseNumber) {
                return current->course;
            }
            else if (courseNumber < current->course.courseNumber) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        Course course;
        course.courseNumber = "";
        return course;
    }
};

void LoadCourses(string fileName, BinarySearchTree& bst) {
    ifstream file(fileName);

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        getline(ss, course.courseNumber, ',');
        getline(ss, course.courseTitle, ',');

        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        bst.Insert(course);
    }

    file.close();

    cout << "Courses loaded successfully." << endl;
}

int main() {
    BinarySearchTree bst;
    int choice = 0;

    while (choice != 9) {
        cout << "\nWelcome to the course planner.\n" << endl;
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl;
        cout << "\nWhat would you like to do? ";

        cin >> choice;

        switch (choice) {
        case 1: {
            string fileName;
            cout << "Enter file name: ";
            cin >> fileName;
            LoadCourses(fileName, bst);
            break;
        }

        case 2:
            cout << "\nHere is a sample schedule:\n" << endl;
            bst.InOrder();
            break;

        case 3: {
            string courseNumber;
            cout << "What course do you want to know about? ";
            cin >> courseNumber;

            Course course = bst.Search(courseNumber);

            if (course.courseNumber == "") {
                cout << "Course not found." << endl;
            }
            else {
                cout << course.courseNumber << ", " << course.courseTitle << endl;

                if (course.prerequisites.size() > 0) {
                    cout << "Prerequisites: ";
                    for (int i = 0; i < course.prerequisites.size(); i++) {
                        cout << course.prerequisites[i];
                        if (i < course.prerequisites.size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << endl;
                }
                else {
                    cout << "Prerequisites: None" << endl;
                }
            }
            break;
            }

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}