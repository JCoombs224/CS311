// Name: Jamison Coombs
// Student ID: 201025791
// Email: coomb010@cougars.csusm.edu

#include <iostream>

struct Student
{
    std::string studentID;
    std::string name;
    int age;
    double currentGPA;
    Student(){}
    Student(std::string id, std::string name, int age, double currentGPA)
    {
        studentID = id;
        this->name = name;
        this->age = age;
        this->currentGPA = currentGPA;
    }
    ~Student(){}
};

unsigned long hash(std::string str)
{
    unsigned long hash = 5381;
    for(int i = 0; i < str.size(); i++)
        hash = hash * str[i] * 33;
    return hash;
}

template<class T>
class Entry
{
    std::string key;
    T* value;
    
    public:
        Entry *next; // next entry at that hash position

        Entry()
        {
            next = NULL;
        }
        Entry(std::string key, T* value)
        {
            this->key = key;
            this->value = value;
            next = NULL;
        }
        std::string getKey()
        {
            return key;
        }
        T* getValue()
        {
            return value;
        }
        ~Entry()
        {
            delete value;
        }
};

template<class T>
class HashMap
{
    Entry<T> **table;
    int size;
    public:
        HashMap(int size)
        {
            this->size = size;
            table = new Entry<T>*[size];
            for(int i = 0; i < size; i++)
                table[i] = NULL;
        }
        void put(Entry<T> *e)
        {
            std::string key = e->getKey();
            int index = hash(key) % size;
            Entry<T> *temp = table[index];

            if(temp == NULL)
            {
                table[index] = e;
                return;
            }
            if(temp->getKey() == key) 
            {
                table[index] = e;
                return;
            }
            while(temp->next != NULL && temp->next->getKey() != key)
            {
                temp = temp->next;
            }
            temp->next = e;
        }
        Entry<T>* getEntry(std::string key)
        {
            int index = hash(key) % size;
            Entry<T> *temp = table[index];
            while(temp != NULL && temp->getKey() != key)
            {
                temp = temp->next;
            }
            return temp;
        }
        T* get(std::string key)
        {
            Entry<T> *temp = getEntry(key);
            if(temp == NULL) return NULL;

            return temp->getValue();
        }
        ~HashMap()
        {
            for(int i = 0; i < size; i++)
                if(table[i] != NULL)
                {
                    Entry<T> *temp = table[i];
                    Entry<T> *next;
                    while(temp != NULL)
                    {
                        next = temp->next;
                        delete temp;
                        temp = next;
                    }
                }
                    
            delete[] table;
        }
        class Overflow{};
};

int main()
{
    // Create student objects

    // Student stu("ID", "name", age, gpa)
    Student *preHashStudents[10];
    preHashStudents[0] = new Student("0123456789", "John", 18, 3.98);
    preHashStudents[1] = new Student("9012345678", "Abby", 20, 3.72);
    preHashStudents[2] = new Student("8901234567", "Ben", 21, 2.50);
    preHashStudents[3] = new Student("7890123456", "Vince", 19, 2.60);
    preHashStudents[4] = new Student("6789012345", "Megan", 19, 2.70);
    preHashStudents[5] = new Student("5678901234", "Hannah", 18, 2.80);
    preHashStudents[6] = new Student("4567890123", "James", 22, 2.90);
    preHashStudents[7] = new Student("3456789012", "Jared", 20, 3.00);
    preHashStudents[8] = new Student("2345678901", "Zach", 20, 3.10);
    preHashStudents[9] = new Student("1234567890", "Bailey", 23, 3.20);

    HashMap<Student> *map = new HashMap<Student>(20);
    for(int i = 0; i < 10; i++)
        map->put(new Entry<Student>(preHashStudents[i]->studentID, preHashStudents[i]));

    Student *postHashStudents[10];
    postHashStudents[0] = map->get("0123456789");
    postHashStudents[1] = map->get("9012345678");
    postHashStudents[2] = map->get("8901234567");
    postHashStudents[3] = map->get("7890123456");
    postHashStudents[4] = map->get("6789012345");
    postHashStudents[5] = map->get("5678901234");
    postHashStudents[6] = map->get("4567890123");
    postHashStudents[7] = map->get("3456789012");
    postHashStudents[8] = map->get("2345678901");
    postHashStudents[9] = map->get("1234567890");

    // Print student info before hashing
    std::cout << "Student info before hashing.\n";
    for (int i = 0; i < 10; i++)
    {
        std::cout << "StudentID: " << preHashStudents[i]->studentID << "; Name: " << preHashStudents[i]->name 
                  << "; Age: " << preHashStudents[i]->age << "; GPA: " << preHashStudents[i]->currentGPA << "\n";
    }

    // Print student info from the hashmap using the id as a key
    std::cout << "\nStudent info after hashing.\n";
    for (int i = 0; i < 10; i++)
    {
        std::cout << "StudentID: " << postHashStudents[i]->studentID << "; Name: " << postHashStudents[i]->name 
                  << "; Age: " << postHashStudents[i]->age << "; GPA: " << postHashStudents[i]->currentGPA << "\n";
    }

    return 0;
}