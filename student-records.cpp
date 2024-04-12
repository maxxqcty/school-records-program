#include <iostream>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <limits>
#include <windows.h>
#include <sstream>

using namespace std;

const int student_count = 50;
const int subjects_count = 4;

struct Student {
string LN, name, sex, age;
   double grades[subjects_count] = {};
};

void saveDataToFile( Student student_list[], int count);
void loadDataFromFile(Student student_list[], int& count);
void add_student(Student student_list[], int& count);
void update_grades( Student student);
void input_grade( Student student_list[], int count);
void update_edit_grades(const Student& student);
void edit_grade( Student student_list[], int count);
void display_grades( Student student_list[], int count);
void display_all_students( Student student_list[], int count);
void edit_student(Student student_list[], int count);
void deleteStudent(Student student_list[], int& count);
void resetDatabase(Student student_list[], int& count);

bool isNumber(const string& str) {

    for (size_t i = 0; i < str.size(); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}
void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void textLabel(){
setTextColor(11);
 cout<<  "\t ___ _____ _   _ ___  ___ _  _ _____   ___ ___ ___ ___  ___ ___  ___    ___ ___  ___   ___ ___   _   __  __ \n"
      				 "\t/ __|_   _| | | |   \\| __| \\| |_   _| | _ | __/ __/ _ \\| _ |   \\/ __|  | _ | _ \\/ _ \\ / __| _ \\ /_\\ |  \\/  |\n"
            	     "\t\\__ \\ | | | |_| | |) | _|| .` | | |   |   | _| (_| (_) |   | |) \\__ \\  |  _|   | (_) | (_ |   // _ \\| |\\/| |\n"
             		 "\t|___/ |_|  \\___/|___/|___|_|\\_| |_|   |_|_|___\\___\\___/|_|_|___/|___/  |_| |_|_\\\\___/ \\___|_|_/_/ \\_|_|  |_|\n";
setTextColor(7);
}
int main() {

    Student student_list[student_count];
    int count = 0;
    int choice;

  loadDataFromFile(student_list, count);

    while (true) {
        system("cls");

    textLabel();
  cout <<"\n\t===========================================================\n\n";
  setTextColor(4);
         cout << "\tWelcome to the School Records Management System!\n"  
  "\tThis program allows you to manage student records efficiently.\n" 
     "\tYou can add new student records and view existing ones easily.\n\n" 
      "\tCreated by: Maximilian Axel E. Enolpe\n\n\n";
      setTextColor(7);
        cout <<"\t---------------------- MENU ------------------------------\n"
    "\t<1> ADD STUDENT \n"
            "\t<2> INPUT GRADE \n"
          "\t<3> EDIT GRADE \n"
            "\t<4> DISPLAY STUDENT DATA \n"
            "\t<5> SHOW ALL STUDENT DATA \n"
            "\t<6> EDIT STUDENT DATA \n"
             "\t<7> DELETE STUDENT DATA \n"
            "\t<8> RESET ALL DATA \n"
            "\t<9> EXIT\n"
            "\t---------------------------------------------------------- \n\n";
        cout << "\tEnter choice: ";
    string input;
        getline(cin, input);

        if (input.length() == 1 && isdigit(input[0])) {
            int choice = input[0] - '0';

        switch (choice) {
            case 1:
                system ("cls");
                add_student(student_list, count);
                getch();
                system("cls");
                textLabel();
                cout <<"\n\t=================== STUDENT RECORDS =================== \n\n";
                cout <<"\tDATA SAVED!\n\n";
                cout <<"\tPress any key to continue...";

                 cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                system("cls");
                 saveDataToFile(student_list, count);
                break;

            case 2:
                system ("cls");
                input_grade(student_list, count);

                 cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                system("cls");
                  saveDataToFile(student_list, count);
                break;
            case 3:
                system ("cls");
                edit_grade(student_list, count );
                 cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                system("cls");
                  saveDataToFile(student_list, count);
                break;

            case 4 :
          system ("cls");
          display_grades(student_list, count);
          getch();
          cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
          system("cls");
                break;
            case 5:
              system("cls");
            display_all_students(student_list, count);
            getch();
             cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            system("cls");
                break;
            case 6:
                system("cls");
                edit_student(student_list, count);

 cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                system("cls");
                saveDataToFile(student_list, count);
                break;  

                   case 7:
                system("cls");
               deleteStudent(student_list, count);
                getch();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                system("cls");
                saveDataToFile(student_list, count);
                break;



            case 8:
                system("cls");
                resetDatabase(student_list, count);
                getch();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                system("cls");
                saveDataToFile(student_list, count);
                break;
                case 9:
                  return 0;


               default: 
    cout << "\tInvalid input";
    cout << "\n\tPress any key to continue...";
getch();
    break;
        }
    }    else {
            cout << "\tInvalid input.";
            cout << "\n\tPress any key to continue...";
            getch();
        }
    }

}

void saveDataToFile(Student student_list[], int count) {
    ofstream outFile("student_data.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < count; i++) {
            outFile << student_list[i].LN << " \""
                    << student_list[i].name << "\" "
                    << student_list[i].age << " "
                    << student_list[i].sex << " ";
            for (int j = 0; j < 4; j++) {
                outFile << student_list[i].grades[j] << " ";
            }
            outFile << endl;
        }
        outFile.close();
    }
}

void loadDataFromFile(Student student_list[], int& count) {
    ifstream StudentsFile("student_data.txt");
    if (StudentsFile.is_open()) {
        count = 0;
        string line;
        while (getline(StudentsFile, line)) {
            istringstream iss(line);
            if (iss >> student_list[count].LN) {
              
                iss >> ws; 
                if (iss.peek() == '"') {
                    iss.get(); 
                    getline(iss, student_list[count].name, '"');
                } else {
                    iss >> student_list[count].name;
                }
          
                iss >> student_list[count].age >> student_list[count].sex;
                for (int j = 0; j < 4; j++) {
                    iss >> student_list[count].grades[j];
                }
                count++;
            }
        }
        StudentsFile.close();
    }
}

void add_student(Student student_list[], int& count) {
    Student new_data;
    textLabel();
    cout << "\n\t===================== ADD STUDENT ===================== \n";

    while (true) {
        cout << "\n\tEnter student LN: ";
        getline(cin, new_data.LN);

        if (!isNumber(new_data.LN) || new_data.LN.empty()) {
            cout << "\tError: Invalid input.\n";
            continue;
        }
        bool isDuplicate = false;
        for (int i = 0; i < count; ++i) {
            if (new_data.LN == student_list[i].LN) {
                isDuplicate = true;
                cout << "\tError: Student LN already exist.\n";
                break;
            }
        }
        if (isDuplicate) {
            continue;
        }

        break;  
    }


    while (true) {
        cout << "\tEnter student name: ";
        getline(cin, new_data.name);

        if (new_data.name.empty()) {
            cout << "\tError: Invalid input. Name cannot be blank.\n";
            continue;
        }

        bool validName = true;
        for (size_t i = 0; i < new_data.name.size(); ++i) {
            if (!isalpha(new_data.name[i]) && !isspace(new_data.name[i]) && new_data.name[i] != '.') {
                validName = false;
                break;
            }
        }

        if (!validName) {
            cout << "\tError: Invalid input. Name should contain only letters and spaces.\n";
            continue;
        }

        break;
    }

    while (true) {
        cout << "\tEnter student age: ";
        getline(cin, new_data.age);

        if (!isNumber(new_data.age) || new_data.age.empty()) {
            cout << "\tError: Invalid input. Age should contain only numbers.\n\n";
            continue;
        }

        break;
    }

    while (true) {
        cout << "\tEnter student sex: ";
        getline(cin, new_data.sex);

        if (new_data.sex.empty()) {
            cout << "\tError: Invalid input. Sex cannot be blank\n";
            continue;
        }

        if (new_data.sex != "Male" && new_data.sex != "Female" || new_data.sex.empty() ) {
            cout << "\tError: Invalid input.\n\n";
            continue;
        }

        break;
    }

    student_list[count] = new_data;
    count++;
}

void update_grades(Student student) {
    cout << "\n\tGrades of " << student.name<< ":\n";

    cout << "\t<1> Math: ";
    if (student.grades[0] != 0.0) {
        cout << student.grades[0]<< "%";
    } else {
        cout << "N/A";
    }
    cout << endl;

    cout << "\t<2> Science: ";
    if (student.grades[1] != 0.0) {
        cout << student.grades[1]<< "%";
    } else {
        cout << "N/A";
    }
    cout << endl;

    cout << "\t<3> English: ";
    if (student.grades[2] != 0.0) {
        cout << student.grades[2]<< "%";
    } else {
        cout << "N/A";
    }
    cout << endl;

    cout << "\t<4> Filipino: ";
    if (student.grades[3] != 0.0) {
        cout << student.grades[3]<< "%";
    } else {
        cout << "N/A";
    }
    cout << endl;
}
void input_grade(Student student_list[], int count) {
    string LN;
    bool found = false;
    int subject;
    double grade;
textLabel();
    cout << "\n\t=================== INPUT GRADES =================== \n\n";
    cout << "\n\tEnter LN: ";
   getline(cin, LN);

    while (LN.empty() || !isNumber(LN)) {
        cout << "\tInvalid LN. Please enter a valid LN.\n";
        cout << "\n\tEnter LN: ";
         getline(cin, LN);

    }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
    textLabel();
    cout << "\n\t=================== INPUT GRADES =================== \n\n";

    for (int i = 0; i < count; i++) {
        if (LN == student_list[i].LN) {
            found = true;

            bool displayGrades = true;

            do {
                if (displayGrades) {
                    update_grades(student_list[i]);
                }
  cout << "\n\t----------------------------------------------------";
                cout << "\n\tSUBJECTS \n\n"
                     << "\t<1> Math\n"
                     << "\t<2> Science\n"
                     << "\t<3> English\n"
                     << "\t<4> Filipino\n"
                     << "\t<5> Exit";
                        cout << "\n\t----------------------------------------------------";
                    cout << "\n\tEnter choice: ";


                cin >> subject;

                while (cin.fail() || subject < 1 || subject > 5) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\n\tInvalid choice. Please enter a valid option.\n";
                    cout << "\n\tEnter choice: ";
                    cin >> subject;
                }

                if (subject == 5) {
                    displayGrades = false;
                    system("cls");
                    textLabel();
                    cout << "\n\t=================== STUDENT RECORDS =================== \n\n";
                    cout << "\tDATA SAVED!\n\n";
                    cout << "\tPress any key to continue...";
                    getch();
                } else {
                    if (student_list[i].grades[subject - 1] != 0.0) {
                        cout << "\tGrade already recorded for this subject.\n";
                        getch();
                    } else {
                        cout << "\n\tEnter grade: ";
                        cin >> grade;

                        while (cin.fail() || grade < 0.0 || grade > 100.0 || cin.peek() != '\n') {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "\n\tInvalid input. Please enter a valid grade.\n";
                            cout << "\n\tEnter grade: ";
                            cin >> grade;
                        }

                        student_list[i].grades[subject - 1] = grade;
                    }
                }

                system("cls");
                textLabel();
                cout << "\n\t=================== INPUT GRADES =================== \n\n";
            } while (subject != 5);
        }
    }

    if (!found) {
        cout << "\n\tStudent not found" << endl;
    }
}

void update_edit_grades(const Student& student) {
    cout << "\n\tGrades of " << student.name << ":\n";

    bool noGrade = true;

    if (student.grades[0] != 0.0) {
        cout << "\t<1> Math: " << student.grades[0] << "%" << endl;
        noGrade =false;
    }

    if (student.grades[1] != 0.0) {
        cout << "\t<2> Science: " << student.grades[1] << "%" << endl;
        noGrade =false;
    }

    if (student.grades[2] != 0.0) {
        cout << "\t<3> English: " << student.grades[2] << "%" << endl;
        noGrade =false;
    }

    if (student.grades[3] != 0.0) {
        cout << "\t<4> Filipino: " << student.grades[3] << "%" << endl;
        noGrade =false;
    }
      if (noGrade) {
        cout << "\tNo grades to edit." << endl;
    }

}
void edit_grade(Student student_list[], int count) {
    string LN;
    bool found = false;
    int subject;
    double grade;
textLabel();
    cout << "\n\t=================== EDIT GRADES =================== \n\n";
    do {
        cout << "\n\n\tEnter student LN: ";
        getline(cin, LN);

        if (LN.empty()) {
            cout << "\tError: Invalid input. LN cannot be blank.";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
    textLabel();
        cout << "\n\t=================== EDIT GRADES =================== \n\n";

        for (int i = 0; i < count; i++) {
            if (LN == student_list[i].LN) {
                found = true;

                bool displayGrades = true;

                do {
                    if (displayGrades) {
                        update_edit_grades(student_list[i]);
                    }
  cout << "\n\t----------------------------------------------------";
                    cout << "\n\tSUBJECTS \n\n"
                         << "\t<1> Math\n"
                         << "\t<2> Science\n"
                         << "\t<3> English\n"
                         << "\t<4> Filipino\n"
                         << "\t<5> Exit";
                    cout << "\n\t----------------------------------------------------\n";
                      cout   << "\n\tEnter choice: ";

                    cin >> subject;

                    while (cin.fail() || subject < 1 || subject > 5 || student_list[i].grades[subject - 1] == 0.0) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if (student_list[i].grades[subject - 1] == 0.0) {
                            cout << "\n\tNo grade recorded for this subject. Please input grade first\n";
                        } else {
                            cout << "\n\tInvalid choice. Please enter a valid option.\n";
                        }
                        cout << "\n\tEnter choice: ";
                        cin >> subject;
                    }

                    if (subject == 5) {
                        displayGrades = false;
                        system("cls");
                        textLabel();
                        cout << "\n\t=================== STUDENT RECORDS =================== \n\n";
                        cout << "\tDATA SAVED!\n\n";
                        cout << "\tPress any key to continue...";
                        getch();
                    } else {
                        cout << "\n\tEnter New grade: ";
                        cin >> grade;

                        while (cin.fail() || cin.peek() != '\n') {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "\n\tInvalid input. Please enter a valid grade.\n";
                            cout << "\n\tEnter New grade: ";
                            cin >> grade;
                        }

                        student_list[i].grades[subject - 1] = grade;
                    }

                    system("cls");
                    textLabel();
                    cout << "\n\t=================== EDIT GRADES =================== \n\n";
                } while (subject != 5);
            }
        }

        if (!found) {
            cout << "\n\tStudent not found" << endl;
        }

    } while (LN.empty());
}

void display_all_students(Student student_list[], int count) {
    string subjects[] = {"Math", "Science", "English", "Filipino"};
    textLabel();

    cout << "\n\t\t\t    =================== ALL STUDENTS AND GRADES =================== \n\n";

    int nameWidth = 35;
    int lnWidth = 25;
    int subjectWidth = 10;
    int gradeWidth = 10;

   for (int i = 0; i < count; i++) {
        if (student_list[i].name.length() > nameWidth) {
            nameWidth = student_list[i].name.length();
        }
        if (student_list[i].LN.length() > lnWidth) {
            lnWidth = student_list[i].LN.length();
        }
    }
cout << "\t------------------------------------------------------------------------------------------------------------\n";
    cout << left << setw(nameWidth) << "\tName" << setw(lnWidth) << "LN";
    for (int subjectIndex = 0; subjectIndex < 4; subjectIndex++) {
        cout << setw(subjectWidth) << subjects[subjectIndex];
    }
    cout << setw(gradeWidth - 3) << "Average\n";
cout << "\t------------------------------------------------------------------------------------------------------------\n\n";
   for (int i = 0; i < count; i++) {
    cout << "\t"<< left << setw(nameWidth) << student_list[i].name << setw(lnWidth) << student_list[i].LN;

    double total = 0.0;
    int numGradesEntered = 0;  

    for (int j = 0; j < 4; j++) {
        if (student_list[i].grades[j] == 0) {
            cout << setw(gradeWidth) << "N/A";
        }
		
		else if (student_list[i].grades[j] < 75.00) {
            cout << setw(gradeWidth)<<" F";
              total += student_list[i].grades[j];
       numGradesEntered++;
        } else {
            cout << std::fixed << std::setprecision(2) << setw(gradeWidth) << student_list[i].grades[j];
            total += student_list[i].grades[j];
            numGradesEntered++;
        }
    }
    if (numGradesEntered > 0) {
        double average = total / numGradesEntered;  
        cout << std::fixed << std::setprecision(2) << setw(gradeWidth) << average;
    } else {
        cout << setw(gradeWidth) << "N/A"; 

  
}
 cout << "\n";
}
}

void display_grades( Student student_list[], int count) {

  string subjects[] = {"Math", "Science", "English", "Filipino"};

    string LN;
    textLabel();
      cout <<"\n\t=================== DISPLAY GRADES =================== \n\n";
    while (true) {
        cout << "\n\n\tEnter student LN: ";
        getline(cin,LN);


        if (!isNumber(LN) || LN.empty()) {
            cout << "\tError: Invalid input.";
            continue;
        }
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
       
        system ("cls");
        textLabel();
     cout <<"\n\t=================== DISPLAY GRADES =================== \n\n";
    bool found = false;
    for(int i = 0; i < count; i++) {
        if(student_list[i].LN == LN) {
            found = true;
            cout << "\tName: " << student_list[i].name<< setw(35 - student_list[i].name.length()) <<"LN: "<< student_list[i].LN << endl;
              cout << "\tSex: " << student_list[i].sex<< setw(37 - student_list[i].sex.length()) << "Age: " << student_list[i].age << "\n\n";
              cout << "\tGRADES\n\n";
            for(int j = 0; j < 4; j++) {
                cout <<"\t"<< subjects[j] << ": ";
                if(student_list[i].grades[j] == 0) {
                    cout << "N/A" << endl;
                } else {
                    cout << student_list[i].grades[j] <<"%" <<endl;
                }
            }
            cout << "\n\t----------------------------------------------------";
       return;
        }
    }
    if (!found) {
        cout << "\tStudent not found" << endl;
    }
}
}
void edit_student(Student student_list[], int count) {
    string LN;
    bool found = false;
    bool dataUpdated = false;
textLabel();
    cout << "\n\t=================== EDIT STUDENT DATA =================== \n\n";

    while (true) {
        cout << "\n\n\tEnter student LN: ";
        getline(cin, LN);

        if (!isNumber(LN) || LN.empty()) {
            cout << "\tError: Invalid input.";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        textLabel();
        cout << "\n\t=================== EDIT STUDENT DATA =================== \n\n";

        for (int i = 0; i < count; i++) {
            if (LN == student_list[i].LN) {
                found = true;

                cout << "\n\tCurrent Information for Student " << student_list[i].LN << ":\n";
                cout << "\tName: " << student_list[i].name << "\n";
                cout << "\tAge: " << student_list[i].age << "\n";
                cout << "\tSex: " << student_list[i].sex << "\n";
                cout << "\n\t------------------------------------------------------------------\n";

                cout << "\n\tEnter new Data.\n";

         
                cout << "\tNew Name: ";
                while (true) {
                    getline(cin, student_list[i].name);
                    if (student_list[i].name.empty()) {
                        cout << "\tError: Invalid input. Name cannot be blank.\n";
                    } else {
                        bool validName = true;
                        for (size_t j = 0; j < student_list[i].name.size(); ++j) {
                            if (!isalpha(student_list[i].name[j]) && !isspace(student_list[i].name[j]) && student_list[i].name[j] != '.') {
                                validName = false;
                                break;
                            }
                        }
                        if (!validName) {
                            cout << "\tError: Invalid input. Name should contain only letters and spaces.\n";
                        } else {
                            break;
                        }
                    }
                    cout << "\tEnter new Name: ";
                }
                cout << "\tNew Age: ";
                while (true) {
                    getline(cin, student_list[i].age);
                    if (!isNumber(student_list[i].age) || student_list[i].age.empty()) {
                        cout << "\tError: Invalid input. Age should contain only numbers.\n\n";
                    } else {
                        break;
                    }
                    cout << "\tEnter new Age: ";
                }
                cout << "\tNew Sex: ";
                while (true) {
                    getline(cin, student_list[i].sex);
                    if (student_list[i].sex.empty()) {
                        cout << "\tError: Invalid input. Sex cannot be blank\n";
                    } else if (student_list[i].sex != "Male" && student_list[i].sex != "Female") {
                        cout << "\tError: Invalid input.\n\n";
                    } else {
                        break;
                    }
                    cout << "\tEnter new Sex: ";
                }

                system("cls");
                textLabel();
                cout << "\n\t=================== STUDENT RECORDS =================== \n\n";
                cout << "\tSTUDENT DATA UPDATED SUCCESSFULLY\n\n";
                cout << "\tPress any key to continue...";
                dataUpdated = true;  
                break;
            }
        }

        if (!found) {
            cout << "\n\tStudent not found" << endl;
            break; 
        }

        if (dataUpdated) {
            break; 
        }
    }
}

void deleteStudent(Student student_list[], int& count) {
  textLabel();
   cout <<  "\n\t=================== RESET DATABASE  =================== \n\n";
    cout << "\n\n\tEnter the LN of the student you want to delete: ";
    string LN;
    cin >> LN;
        int indexToDelete = -1; 

    for (int i = 0; i < count; ++i) {
        if (student_list[i].LN == LN) {
            indexToDelete = i;
            break; 
        }
    }

    if (indexToDelete != -1) {
       cout << "\n\tAre you sure you want to delete the student with LN " << LN << "? (Y/N): ";
    char confirmation;
    cin >> confirmation;

    if (toupper(confirmation) == 'Y') {
        for (int i = indexToDelete; i < count - 1; ++i) {
            student_list[i] = student_list[i + 1];
        }


        --count;

        cout << "\n\tStudent " << LN << " has been deleted.\n";
    } 
} else {
        cout << "\n\tStudent not found. Deletion canceled.\n";
  
    }
}

void resetDatabase(Student student_list[], int& count) {
  textLabel();
    cout <<  "\n\t=================== RESET DATABASE  =================== \n\n"
  "\n\n\tAre you sure you want to reset the database? (Y/N): ";
    char choice;
    cin >> choice;

    if (toupper(choice) == 'Y') {
        count = 0; 
          system("cls");
          textLabel();
                cout << "\n\t=================== RESET DATABASE =================== \n\n";
                cout << "\tDATABASE RESET!\n\n";
                cout << "\tPress any key to continue...";

    } else {
        cout << "\n\tReset canceled.\n";
    }
}


