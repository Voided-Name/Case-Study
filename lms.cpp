#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <conio.h>
#include <iterator>

using namespace std;
string encrypt(string password)
{
    string en_password;
    const string KEY = "CICT";
    int y = 0, key_last = KEY.length() - 1;
    int en_char;

    for (int x = 0; x < password.length(); x++)
    {
        int pass_x = password[x];
        int key_y = KEY[y];
        en_char = pass_x + key_y;

        if (en_char > 125)
        {
            en_char = en_char - 125 + 32;
        }

        if (en_char == 59)
        {
            en_char = 126;
        }

        en_password += en_char;
        if (y == key_last)
        {
            y = 0;
        }
        else
        {
            y++;
        }
    }

    return en_password;
}

string decrypt(string password)
{
    string dec_password;
    const string KEY = "CICT";
    int y = 0, key_last = KEY.length() - 1;
    int en_char;

    for (int x = 0; x < password.length(); x++)
    {
        en_char = password[x];

        if (en_char == 126)
        {
            en_char = 59;
        }
        if (en_char < 33 + KEY[y])
        {
            en_char = en_char - 32 + 125 - KEY[y];
        }

        dec_password += en_char;

        if (y == key_last)
        {
            y = 0;
        }
        else
        {
            y++;
        }
    }

    return dec_password;
}
// uses a for loop to check if any of the character in the string is a whitespace
bool has_white_space(string buffer)
{
    for (int x = 0; x < buffer.length(); x++)
    {
        if (!isspace(buffer[x]))
        {
            if (x == buffer.length() - 1)
            {
                return true;
                break;
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}

char logreg()
{
    char loginform = 'c';
    string loginform_str;

    cout << "Welcome To Library Management System\na. Login\nb. Register (wait for admin authentication after registration)\n: ";

    while (true)
    {
        getline(cin, loginform_str);
        loginform = loginform_str[0];
        if (loginform != 'a' && loginform != 'b' || loginform_str.length() > 1)
        {
            cout << "Invalid Input \""
                 << loginform_str << "\"\na.Login\nb.Register\n : ";
        }
        else
        {
            break;
        }
    }

    return loginform;
}

int authenticate(string username, string password)
{
    int line_num = 1;
    ifstream file("authdata.txt");
    string fusername, fpassword;

    while (file)
    {
        getline(file, fusername, ';');
        getline(file, fpassword);

        if (fusername == username && fpassword == password)
        {
            cout << endl
                 << "Logged In" << endl;
            return line_num;
        }
        line_num++;
    }

    cout << endl
         << "Invalid Credentials" << endl;
    return 0;
}
// input username and password, user authentication password to verify password
string logging_in()
{
    string username, password;
    char ch;
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    ch = getch();
    while (ch != 13)
    {
        if (ch == 3)
        {
            abort();
        }
        if (ch == 8)
        {
            cout << "\b \b";
            password.pop_back();
            ch = getch();
            continue;
        }
        password.push_back(ch);
        cout << '*';
        ch = getch();
    }

    if (username == "admin" && password == "1234")
    {
    }

    int id = authenticate(encrypt(username), encrypt(password));

    if (id != 0)
    {
        return "true " + username + " " + to_string(id);
    }
    else
    {
        return "false";
    }
}

string username_reg()
{
    string username_buffer, username;
    bool cont = false;

    while (cont == false)
    {
        cout << "Username (Don't Use Whitespaces): ";
        getline(cin, username_buffer);
        cont = has_white_space(username_buffer);
    }

    return username_buffer;
}

string password_reg()
{
    string password;
    bool upper_true = false, number_true = false;
    char ch;

    while (true)
    {
        cout << "Password (at least one uppercase letter and one number, don't user whitespaces): ";
        ch = getch();

        while (ch != 13)
        {
            if (ch == 3)
            {
                abort();
            }
            if (ch == 8)
            {
                cout << "\b \b";
                password.pop_back();
                ch = getch();
                continue;
            }
            password.push_back(ch);
            cout << '*';
            ch = getch();
        }

        for (int x = 0; x < password.length(); x++)
        {
            if (password[x] >= 65 && password[x] <= 90)
            {
                upper_true = true;
            }
            if (password[x] >= 48 && password[x] <= 57)
            {
                number_true = true;
            }
        }

        if (upper_true && number_true)
        {
            break;
        }
        else
        {
            cin.clear();
            cout << endl
                 << "Invalid Input! Please Try Again" << endl;
        }
    }

    cout << endl;

    return password;
}

string email_reg()
{
    string email;

    while (true)
    {
        bool has_at = false, has_period = false;
        cout << "Email: ";
        cin >> email;

        for (int x = 0; x < email.length(); x++)
        {
            if (email[x] == '@')
            {
                has_at = true;
            }
            if (has_at && email[x] == '.')
            {
                has_period = true;
            }
        }

        if (has_at && has_period)
        {
            return email;
        }
        else
        {
            cout << "Enter a valid email" << endl;
            continue;
        }
    }
    return email;
}

void registration()
{
    string username, username_buffer, password, email, fname, lname, role;
    char role_c = 'c';

    username = username_reg();
    password = password_reg();
    email = email_reg();

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "First Name: ";
    getline(cin, fname);
    cout << "Last Name: ";
    getline(cin, lname);
    do
    {
        cout << "Role\na. Student, b. Faculty: ";
        cin >> role_c;
    } while (role_c != 'a' && role_c != 'b');
    if (role_c == 'a')
    {
        role = "student";
    }
    else
    {
        role = "faculty";
    }

    ofstream twrite("toberegistered.txt");

    if (twrite.is_open())
    {
        twrite << encrypt(username) << ";" << encrypt(password) << ";" << encrypt(email) << ";" << encrypt(fname) << ";" << encrypt(lname) << ";" << encrypt(role) << endl;
    }
}
bool mycomp(string a, string b)
{
    return a < b;
}
void sort_alph()
{
    string str;
    vector<string> books_vec;

    fstream books;
    books.open("books/books.txt", ios::in);

    ofstream books_alph("books/books_alph.txt");
    ostream_iterator<string> output_iterator(books_alph, "\n");

    while (getline(books, str, ';'))
    {
        books_vec.push_back(str);
        getline(books, str);
    }

    sort(books_vec.begin(), books_vec.end());
    copy(books_vec.begin(), books_vec.end(), output_iterator);
}

int main()
{
    string logged_in;
    // logging in
    while (true)
    {
        char log_reg;

        log_reg = logreg();
        if (log_reg == 'a')
        {
            logged_in = logging_in();
            if (logged_in == "false")
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else
        {
            registration();
        }
    }

    sort_alph();

    string username, id;

    int spaces = 0;
    for (int x = 0; x < logged_in.length(); x++)
    {
        if (logged_in[x] == ' ')
        {
            spaces++;
            continue;
        }
        if (spaces == 1)
        {
            username += logged_in[x];
        }
        else if (spaces == 2)
        {
            id += logged_in[x];
        }
    }

    cout << endl
         << "Welcome " << username;
}