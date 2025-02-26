/*
*Name: CS300 Project 2
*Author: Brad Brennand
*Version: 2.0
*Description: This program is designed to load a file, 
*print info from a file and search for information in a file.
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

//defines a structure to hold course information
struct Course {
    string courseId;
    string courseName;
    vector<string> preReq;
};
// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a course
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

    //displays menu
void DisplayMenu() {
    cout << "1. Load File into Data Structure" << endl;
    cout << "2. Print Course List for CS Program" << endl;
    cout << "3. Print Course with Prequisites" << endl;
    cout << "9. Exit Program" << endl;
    cout << "Please choose an option." << endl;
};

    

    
/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    void Destruct(Node* node);

public:
    Node* root;
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Search(string courseId);
    void Insert(BinarySearchTree* tree, Node* node);
    void PrintCourse(Node* node);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    Destruct(root);
}

/**
 *finds left and right pointer nodes and deletes them
 */
void BinarySearchTree::Destruct(Node* node) {
    if (node != nullptr) {
        Destruct(node->left);
        node->left = nullptr;
        Destruct(node->right);
        node->right = nullptr;
        delete node;
    }
}

/**
*inserts courses into the tree
*/
void BinarySearchTree::Insert(BinarySearchTree* tree, Node* node) {
    //if the trees root equals null than the tree root is the node
    if (tree->root == nullptr) {
        tree->root = node;
    }
    //else current node equals the tree root
    else {
        Node* curr = tree->root;
//while current node is not equal to Null pointer
        while (curr != nullptr) {
            //if courseId less than current node
            if (node->course.courseId < curr->course.courseId) {
                //if left node equals null pointer, than left node is current node
                if (curr->left == nullptr) {
                    curr->left = node;
                    curr = nullptr;
                }
                //else current node becomes left node
                else {
                    curr = curr->left;
                }
            }
            //else
            else {
                //if right node equals null pointer than current node becomes right node
                if (curr->right == nullptr) {
                    curr->right = node;
                    curr = nullptr;
                }
                //else current node is right node
                else {
                    curr = curr->right;
                }
            }

        }

    }
}
/**
*loads file and adds it to tree
*/
void loadfile(string filename, BinarySearchTree* tree) {
    ifstream file(filename);
    //if file is open print file loaded
    if (file.is_open()) {
        cout << "File loaded." << endl;

        int num;
        string line;
        string word;
        //while file is open get line from file
        while (getline(file, line)) {

            num = 0;
            Node* node = new Node();
            stringstream str(line);
            //loop(while number less than 2 get string and word followed by comma and increase number)
            while (num < 2) {
                getline(str, word, ',');
                //if number equals 0, courseId equals word
                if (num == 0) {
                    node->course.courseId = word;
                }
                //else courseName equals word
                else {
                    node->course.courseName = word;
                }
                num++;
            }
            //loop(while file still getting lines add prequisites to end of line
            while (getline(str, word, ',')) {
                node->course.preReq.push_back(word);
            }

            //inserts node into tree
            tree->Insert(tree, node);
        }
    }
    //file error if file not found
    else {
        cout << "File error, please check the filename and try again. (Courses.csv) is Computer science files." << endl;
        return;
    }
}

    //search for a course
void BinarySearchTree::Search(string courseId) {
     Node* curr = root;

     while (curr != nullptr) {
         if (curr->course.courseId == courseId) {
             //prints courseId and courseName
             cout << curr->course.courseId << ", ";
             cout << curr->course.courseName;
             cout << endl;
             cout << "Prerequisites: ";
             //prints all prerequisites, followed by comma if there are more than 1
             for (string preReq : curr->course.preReq) {
                 //if course has a prerequisite than print it at the end of the line
                 if (preReq == curr->course.preReq.back()) {
                     cout << preReq << endl;
                 }
                 //else print prerequisite followed by a comma
                 else {
                     cout << preReq << ", ";
                 }
             }
             return;
         }
         //searches left pointer if not found
         else if (courseId < curr->course.courseId) {
            //if current node not equal to null pointer than current node becomes left node
            if (curr->left != nullptr) {
               curr = curr->left;
            }
         }
         //else searches right pointer if not found
         else {
             curr = curr->right;
         }
     }
     //print: course is not in the list
     cout << "Course " << courseId << " not found, please check the course and try again." << endl;
     return;
}

//prints course list
void BinarySearchTree::PrintCourse(Node* node) {
    //Traverse and print entire tree
    if (node == nullptr) {
        return;
    }

    //looks at the left node, prints course id, course name, then moves to the next node
    PrintCourse(node->left);
    cout << node->course.courseId << ", ";
    cout << node->course.courseName << endl;
    PrintCourse(node->right);
}

int main()
{
    BinarySearchTree* tree = new BinarySearchTree();

    string file;
    string course;

    int userInput = 0;

    cout << "Welcome to the course planner." << endl << endl;
    //main while loop to keep program open while choice is not 9
    while (userInput != 9) {
        DisplayMenu();
        cin >> userInput;

        switch (userInput) {
            //loads file
        case 1:
            cout << "Please enter file name to load." << endl;
            cin >> file;

            loadfile(file, tree);
            cout << endl;
            break;

            //prints courses in alphanumeric order
        case 2:
            cout << endl;
            cout << "------------------------------------------" << endl;
            cout << "COURSE ID |     COURSE NAME" << endl;
            cout << "------------------------------------------" << endl;
            //prints course starting at root   	
            tree->PrintCourse(tree->root);
            cout << endl;
            break;

            //prints courses with prerequisites
        case 3:
            cout << endl;
            cout << "Please enter course Id number. ";
            cin >> course;
            cout << endl;

            transform(course.begin(), course.end(), course.begin(), ::toupper);
            tree->Search(course);

            cout << endl;
            break;

            //exits the program
        case 9:
            cout << "Thank you come again!" << endl;
            break;

            //default message if one of the above choices is not entered
        default:
            cout << userInput << " is an invalid option, Please try again." << endl;
            break;
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
