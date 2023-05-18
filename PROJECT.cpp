#include <bits/stdc++.h>
#include <windows.h>
#define ec cout<<"\n\nEmpty cart\n"
#define err cout<<"\n\nInvalid Entry\n"
using namespace std;


void hello();
void bye();
void __attribute__((constructor)) hello(); //constructor which displays a starting message
void __attribute__((destructor)) bye();     //destructor which displays a message at the end


int num();      //Function to get a integer value, or to re-read entered value if not integer
float flo();    //Function to get a float value, or to re-read entered value if not float




class customer          //a user defined datatype for defining customer objects
{
    char username[100];
    char password[100];     //username and password used for searching and selecting customer object from file
    char name[100];
    int age;
    char location[100];
public:
    void readcustomer();
    void printcustomer();
    int getage();
    char* getu();
    char* getp();
    char* getname();
};
char* customer::getname()
{
    return name;
}
char* customer::getu()
{
    return username;
}
char* customer::getp()
{
    return password;
}
void customer::readcustomer()
{
    cout<<"\n\nEnter new username\t:\t";
    cin.getline(username,99);
    cout<<"Enter new password\t:\t";
    cin.getline(password,99);
    cout<<"Enter name\t:\t";
    cin.getline(name,99);
    cout<<"Enter age\t:\t";
    age=num();
    cout<<"Enter location\t:\t";
    cin.getline(location,99);
    if(strcmp(location,"\0")==0)
        strcpy(location,"Mumbai");
    cout<<"\n";
}
void customer::printcustomer()
{
    cout<<"\n\nCUSTOMER DETAILS :-\nName\t:\t"<<name<<"\nAge\t:\t"<<age<<"\nLocation\t:\t"<<location<<"\n\n";
}
int customer::getage()
{
    return age;
}






class product       //a user defined datatype for defining product objects
{
public:
    char name[100];
    float price;
    int searchcounter;      //used to maintain number of times the product object was inserted into the list
public:
    int age;                //age-group for which the product is meant for
    void readproduct();
    void printproduct();
    char* getname();
};
void product::readproduct()
{
    cout<<"\n\nEnter product name=";
    cin.getline(name,99);
    cout<<"Enter price=";
    price=flo();
    cout<<"Enter age=";
    age=num();
    cout<<"\n\n";
    searchcounter=0;
}
void product::printproduct()
{
    cout<<name<<"\t"<<price<<"\t"<<searchcounter<<"\n";
}
char* product::getname()
{
    return name;
}






class productlist
{
    vector<product> obj[5];         //Array of 5(number of age groups) vectors of product objects
public:
    void newproduct();              //Creates a new product and adds it to obj and also appends it into the file, if name of object matches with existing product object, new object is not added
    void extractfromfile();         //Reads data from the "product.dat" file into the obj vector array
    void deleteproduct();           //removes object from obj and copies content from "product.dat" to "temp.dat", except deleted product object, and removes "product.dat", and renames "temp.dat" to "product.dat"
    void updateproduct();           //removes object from vector, creates and reads new object, and and copies content from "product.dat" to "temp.dat", except deleted product object instead of which new object is inserted, and removes "product.dat", and renames "temp.dat" to "product.dat"
    void displayproduct(int custage);   //displays entire obj vector array according to user age
    product selectproduct();            //searches a product object from the obj vector array and returns it
};
void productlist::newproduct()
{
    product temp;
    temp.readproduct();
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<obj[i].size();j++)
        {
            if(strcmp(temp.getname(),obj[i][j].getname())==0)
            {
                cout<<"\n\nProduct already exists!\n";
                return;
            }
        }
    }
    int index=temp.age<13?0:temp.age<18?1:temp.age<30?2:temp.age<50?3:4;
    obj[index].push_back(temp);
    fstream fout("product.dat",ios::binary|ios::app);
    fout.write((char*)&temp,sizeof(temp));
    fout.close();
    cout<<"\n\nNew product added!\n";
}
void productlist::extractfromfile()
{
    product temp;
    fstream fin("product.dat",ios::binary|ios::in);
    int index;
    while(fin.read((char*)&temp, sizeof(temp)))
    {
        index=temp.age<13?0:temp.age<18?1:temp.age<30?2:temp.age<50?3:4;
        if(obj[index].size()==0||temp.searchcounter==0)
        {
            obj[index].push_back(temp);
        }
        else
        {
            for(int i=0;i<obj[index].size();i++)
            {
                if(temp.searchcounter>=obj[index][i].searchcounter)
                {
                    obj[index].insert(obj[index].begin()+i,temp);
                    break;
                }
            }
        }
    }
    fin.close();
}
void productlist::displayproduct(int custage)
{
    if(obj[0].size()==0&&obj[1].size()==0&&obj[2].size()==0&&obj[3].size()==0&&obj[4].size()==0)
    {
        cout<<"\nNo Products!\n";
        return;
    }
    product tempdisp;
    int age=custage,x=1;
    int index=age<13?0:age<18?1:age<30?2:age<50?3:4;
    if(obj[index].size()!=0)
    {
        index==0?cout<<"AGES 12 AND BELOW :-\n":index==1?cout<<"AGES 13-17 :-\n":index==2?cout<<"AGES 18-29 :-\n":index==3?cout<<"AGES 30-49 :-\n":cout<<"AGES 50 AND ABOVE :-\n";
        cout<<"S.No.\tName\tPrice\tSearch\n";
        for(int i=0;i<obj[index].size();i++,x++)
        {
            cout<<x<<".\t";
            obj[index][i].printproduct();
        }
    }

    for(int i=0;i<5;i++)
    {
        if(i!=index&&obj[i].size()!=0)
        {
            i==0?cout<<"\nAGES 12 AND BELOW :-\n":i==1?cout<<"\nAGES 13-17 :-\n":i==2?cout<<"\nAGES 18-29 :-\n":i==3?cout<<"\nAGES 30-49 :-\n":cout<<"\nAGES 50 AND ABOVE :-\n";
            cout<<"S.No.\tName\tPrice\tSearch\n";
            for(int j=0;j<obj[i].size();j++,x++)
            {
                cout<<x<<".\t";
                obj[i][j].printproduct();
            }
        }
    }
}
void productlist::deleteproduct()
{
    int index,n,x=0,f=0;
    char pname[100];
    product temp;
	cout<<"\nEnter name of product to be removed=";
    cin.getline(pname,99);
    for(index=0;index<5;index++)
    {
        for(x=0;x<obj[index].size();x++)
        {
            if(strcmp(obj[index][x].getname(),pname)==0)
            {
                f=1;
                break;
            }
        }
        if(f==1)
            break;
    }
    if(f==1)
    {
        ifstream fp1;
        fp1.open("product.dat",ios::binary|ios::in);
        ofstream fp2;
        fp2.open("temp.dat",ios::binary|ios::out);
        while(fp1.read((char*)&temp,sizeof(temp)))
        {
            if(strcmp(temp.getname(),obj[index][x].getname())!=0)
                fp2.write((char*)&temp,sizeof(temp));
        }
        fp1.close();
        fp2.close();
        remove("product.dat");
        rename("temp.dat","product.dat");
        obj[index].erase(obj[index].begin()+(x));
        cout<<"\n\nProduct Deleted!\n";
    }
    else
    {
        cout<<"\nProduct not found!\n";
    }
}
void productlist::updateproduct()
{
    product temp;
    int index,x=0,f=0;
    char pname[100];
    cout<<"\nEnter name of product to be updated=";
    cin.getline(pname,99);
    for(index=0;index<5;index++)
    {
        for(x=0;x<obj[index].size();x++)
        {
            if(strcmp(obj[index][x].getname(),pname)==0)
            {
                f=1;
                break;
            }
        }
        if(f==1)
            break;
    }
    if(f==1)
    {
        ifstream fp;
        fp.open("product.dat",ios::binary|ios::in);
        ofstream fp1;
        fp1.open("temp.dat",ios::binary|ios::out);
        while(fp.read((char*)&temp,sizeof(temp)))
        {
            if(strcmp(temp.getname(),obj[index][x].getname())==0)
            {
                cout<<"\n\n";
                obj[index][x].printproduct();
                cout<<"ENTER NEW DETAILS :-\n";
                obj[index][x].readproduct();
                temp=obj[index][x];
                fp1.write((char*)&temp,sizeof(temp));
            }
            else
            {
                fp1.write((char*)&temp,sizeof(temp));
            }
        }
        fp.close();
        fp1.close();
        remove("product.dat");
        rename("temp.dat","product.dat");
        temp=obj[index][x];
        obj[index].erase(obj[index].begin()+(x));
        int index=temp.age<13?0:temp.age<18?1:temp.age<30?2:temp.age<50?3:4;
        obj[index].push_back(temp);
        cout<<"\nProduct updated!\n";
    }
    else
    {
        cout<<"\nProduct not found!\n";
    }
}
product productlist::selectproduct()
{
    product temp,temp1;
    int index,n,x,f=0;
    char pname[100];
    cout<<"\nEnter name of product to be added to cart=";
    cin.getline(pname,99);
    while(f==0)
    {
        for(index=0;index<5;index++)
        {
            for(x=0;x<obj[index].size();x++)
            {
                if(strcmp(obj[index][x].getname(),pname)==0)
                {
                    f=1;
                    break;
                }
            }
            if(f==1)
                break;
        }
        if(f==0)
        {
            cout<<endl<<pname<<"\nProduct not found!\nEnter name of product to be added to cart=";
            cin.getline(pname,99);
        }
    }
    obj[index][x].searchcounter++;
    ifstream fp;
    fp.open("product.dat",ios::binary|ios::in);
    ofstream fp1;
    fp1.open("temp.dat",ios::binary|ios::out);
    while(fp.read((char*)&temp,sizeof(temp)))
    {
        if(strcmp(temp.getname(),obj[index][x].getname())==0)
        {
            temp=obj[index][x];
            fp1.write((char*)&temp,sizeof(temp));
        }
        else
        {
            fp1.write((char*)&temp,sizeof(temp));
        }
    }
    fp.close();
    fp1.close();
    remove("product.dat");
    rename("temp.dat","product.dat");
    temp1=obj[index][x];
    obj[index].erase(obj[index].begin()+x);
    f=0;
    for(int i=0;i<obj[index].size();i++)
    {
        if(temp1.searchcounter>obj[index][i].searchcounter)
        {
            obj[index].insert(obj[index].begin()+i,temp1);
            f=1;
            break;
        }
    }
    if(f==0)
    {
        obj[index].push_back(obj[index][x]);
    }
    return temp1;
}





struct node         //new list node
{
    product data;
    int quantity;
    struct node* prevxnext;     //pointer containing XOR value previous and next node to the current node in the list
};
class List
{
private:
    struct node* start;     //points to first node in the list
    struct node* end;       //points to last node in the last
    float total;            //total amount of objects in the cart
public:
    float gettotal();
    List();                  //sets start and end pointer
    void insertatbeg(product item);     //creates a node, sets prevxnext of first node to XOR of address of newnode and next node and points start to new node and prevxnext of new node as XOR of NULL and first node
    void deleteatbeg();                 //sets prevxnext of second node as XOR of NULL and third node, and points start to second node and frees memory location of first node
    void deleteatend();                 //sets prevxnext of second last node as XOR of NULL and third last node, and points end to second last node and frees memory location of last node
    void del();                         //deletes a specific node and resets prevxnext of surrounding nodes
    void traverse();                    //traverses and displays values of all nodes
    struct node* XOR(struct node*,struct node*);    //type casts argument pointers to int and converts the resultant to pointer and returns the pointer value
    void emptylist();                               //deletes all nodes from list
};
void List::emptylist()
{
    while(start!=NULL&&end!=NULL)
    {
        deleteatbeg();
    }
    total=0;
}
float List::gettotal()
{
    return total;
}
List::List()
{
    start=NULL;
    end=NULL;
    total=0;
}
struct node* List::XOR(struct node* a,struct node* b)
{
    return (struct node*)((uintptr_t)a^(uintptr_t)b);
};
void List::insertatbeg(product item)
{
    struct node* newnode;
    newnode=new struct node;
    if(newnode==NULL)
    {
        cout<<"\n\nCart full!\n\n";
        return;
    }
    cout<<"Enter quantity=";
    newnode->quantity=num();
    newnode->data=item;
    total+=newnode->data.price*newnode->quantity;
    if(start==NULL&&end==NULL)
    {
        newnode->prevxnext=XOR(NULL,NULL);
        start=newnode;
        end=newnode;
    }
    else
    {
        newnode->prevxnext=XOR(NULL,start);
        start->prevxnext=XOR(newnode,XOR(start->prevxnext,NULL));
        start=newnode;
    }
    cout<<"\n\nProduct added to cart.\n";
}
void List::deleteatbeg()
{
    if(start==NULL)
    {
        ec;
        return;
    }
    struct node* nodetodel;
    if(start==end)
    {
        nodetodel=start;
        total-=nodetodel->data.price*nodetodel->quantity;
        start=NULL;
        end=NULL;
        delete nodetodel;
    }
    else
    {
        nodetodel=start;
        total-=nodetodel->data.price*nodetodel->quantity;
        start=XOR(start->prevxnext,NULL);
        start->prevxnext=XOR(NULL,XOR(nodetodel,start->prevxnext));
        delete nodetodel;
    }
}
void List::deleteatend()
{
    if(start==NULL)
    {
        ec;
        return;
    }
    struct node* nodetodel;
    if(start==end)
    {
        nodetodel=start;
        total-=nodetodel->data.price*nodetodel->quantity;
        start=NULL;
        end=NULL;
        delete nodetodel;
    }
    else
    {
        nodetodel=end;
        total-=nodetodel->data.price*nodetodel->quantity;
        end=XOR(end->prevxnext,NULL);
        end->prevxnext=XOR(XOR(end->prevxnext,nodetodel),NULL);
        delete nodetodel;
    }
}
void List::del()
{
    if(start==NULL)
    {
        ec;
        return;
    }
    traverse();
    int position;
    cout<<"\nEnter position of item to be deleted=";
    position=num();
    struct node* tra=start;
    struct node* prev=NULL;
    struct node* n;
    for(int i=1;i<position;i++)
    {
        n=tra;
        tra=XOR(tra->prevxnext,prev);
        prev=n;
        if(tra==NULL)
        {
            cout<<"\n\nEntered position exceeds list size\n";
            return;
        }
    }
    if(position==1)
    {
        deleteatbeg();
    }
    else if(XOR(prev,tra->prevxnext)==NULL)
    {
        deleteatend();
    }
    else
    {
        total-=tra->data.price*tra->quantity;
        (XOR(tra->prevxnext,prev))->prevxnext=XOR(prev,XOR(tra,(XOR(tra->prevxnext,prev))->prevxnext));
        prev->prevxnext=XOR(XOR(prev->prevxnext,tra),XOR(tra->prevxnext,prev));
        delete tra;
    }
    cout<<"\nProduct removed from cart.\n";
}
void List::traverse()
{
    struct node* tra;
    struct node* prev;
    struct node* n;
    int t=0;
    if(start==NULL)
    {
        ec;
        return;
    }
    tra=start;
    prev=NULL;
    cout<<"\n\nQty\tName\tPrice\tSearch\n";
    while(tra!=NULL)
    {
        cout<<tra->quantity<<"\t";
        tra->data.printproduct();
        t+=tra->data.price*tra->quantity;
        n=tra;
        tra=XOR(tra->prevxnext,prev);
        prev=n;
    }
    total=t;
    cout<<"TOTAL\t=\t"<<total<<endl;
}






class user                  //user defined datatype for current user
{
    static int counter;     //maintains total count of all users
    customer obj;           //current user which can perform product related functions
public:
    List cart;              //defines list called cart to store product objects
    int login(char* u,char* p);     //takes string arguments from user, compares it to username and password of objects in file and sets obj as object from file with matching username
    void newuser();                 //creates new customer object, reads it, and adds it to "customer.dat" file
    void deleteuser();              //copies content of "customer.dat" to "temp.dat" except obj, removes "customer.dat" and renames "temp.dat" to "customer.dat"
    void updateuser();              //copies content of "customer.dat" to "temp.dat", instead of copying obj, rereads obj and then copies it to "temp.dat", removes "customer.dat" and renames "temp.dat" to "customer.dat"
    static void pluscount();        //increments counter
    static void minuscount();       //decrements counter
    void showcount();               //displays counter
    int getcustage();               //returns age of obj
    void displayuser();             //displays all customers
};
int user::getcustage()
{
    return obj.getage();
}
int user::counter;
void user::pluscount()
{
    counter++;
}
void user::minuscount()
{
    counter--;
}
int user::login(char* u,char* p)
{
    customer temp;
    fstream fin("customer.dat",ios::binary|ios::in);
    int c=0,f=0;
    while(fin.read((char*)&temp,sizeof(temp))!=0)
    {
        if(strcmp(temp.getu(),u)==0&&strcmp(temp.getp(),p)==0)
        {
            obj=temp;
            f=1;
            break;
        }
    }
    fin.close();
    if(f==0)
    {
        cout<<"\n\nUsername or password does not exist!\n";
        return 0;
    }
    else
    {
        cout<<"\nLogged in!\n";
        cout<<"\nWelcome "<<obj.getname()<<" !\n";
        return 1;
    }
}
void user::newuser()
{
    int f=0;
    customer temp,temp1;
    temp.readcustomer();
    ifstream fin("customer.dat",ios::binary|ios::in);
    while(fin.read((char*)&temp1,sizeof(temp1))!=0)
    {
        if(strcmp(temp1.getu(),temp.getu())==0)
        {
            f=1;
            break;
        }
    }
    fin.close();
    if(f==0)
    {
        fstream fout("customer.dat",ios::binary|ios::app);
        fout.write((char*)&temp,sizeof(temp));
        fout.close();
        pluscount();
        cout<<"\nNew customer account created!\n";
    }
    else
    {
        cout<<"\nUsername already exists!\n";
        return;
    }

}
void user::deleteuser()
{
    customer temp;
    ifstream fp1;
    fp1.open("customer.dat",ios::binary|ios::in);
    ofstream fp2;
    fp2.open("temp.dat",ios::binary|ios::out);
    while(fp1.read((char*)&temp,sizeof(temp))!=0)
    {
        if(strcmp(temp.getu(),obj.getu())!=0)
        {
            fp2.write((char*)&temp,sizeof(temp));
        }
    }
    fp1.close();
    fp2.close();
    remove("customer.dat");
    rename("temp.dat","customer.dat");
    minuscount();
    cout<<"\nUser account deleted!";
}
void user::updateuser()
{
    customer temp,temp1;
    int f=0;
    ifstream fp;
    fp.open("customer.dat",ios::binary|ios::in);
    ofstream fp1;
    fp1.open("temp.dat",ios::binary|ios::out);
    while(fp.read((char*)&temp,sizeof(temp))!=0)
    {
        if(strcmp(temp.getu(),obj.getu())==0)
        {
            obj.printcustomer();
            cout<<"\nENTER NEW DETAILS: -\n";
            obj.readcustomer();
            if(strcmp(temp.getu(),obj.getu())!=0)
            {
                ifstream fc;
                fc.open("customer.dat",ios::binary|ios::in);
                while(fc.read((char*)&temp1,sizeof(temp1))!=0)
                {
                    if(strcmp(temp1.getu(),obj.getu())==0&&strcmp(temp.getu(),temp1.getu())!=0)
                    {
                        f=1;
                        break;
                    }
                }
            }
            if(f==1)
            {
                obj=temp;
                fp1.write((char*)&temp,sizeof(temp));
            }
            else
            {
                temp=obj;
                fp1.write((char*)&temp,sizeof(temp));
            }
        }
        else
        {
            fp1.write((char*)&temp,sizeof(temp));
        }
    }
    fp.close();
    fp1.close();
    if(f==1)
    {
        remove("temp.dat");
        cout<<"\nUsername already exists!\n";
    }
    else
    {
        remove("customer.dat");
        rename("temp.dat","customer.dat");
        cout<<"\nAccount details updated!\n";
    }
}
void user::showcount()
{
    counter=0;
    customer temp;
    ifstream fin("customer.dat",ios::binary|ios::in);
    while(fin.read((char*)&temp,sizeof(temp)))
    {
        pluscount();
    }
    fin.close();
    cout<<"\n\nTotal user accounts="<<counter<<endl;
}
void user::displayuser()
{
    customer temp;
    ifstream fin("customer.dat",ios::binary|ios::in);
    while(fin.read((char*)&temp,sizeof(temp)))
    {
        temp.printcustomer();
    }
    fin.close();
}






class admin
{
    char username[100];
    char password[100];
public:
    admin();
    void modifyproductlist(char* u,char* p,productlist& temp);      //reads strings as arguments and if they match with username and password, allows modification of list items and viewing customers
};
admin::admin()
{
        strcpy(username,"angad");
        strcpy(password,"1510");
}
void admin::modifyproductlist(char* u,char* p,productlist& mainlist)
{
    if(strcmp(username,u)==0&&strcmp(password,p)==0)
    {
        int ch;
        do
        {
            system("CLS");
            mainlist.displayproduct(1);
            cout<<"\n\n1. New product\n2. Delete product\n3. Update product\n4. Display all users\n5. Number of user accounts\n6. Sign out\nEnter choice...";
            ch=num();
            switch(ch)
            {
            case 1:
                {
                    mainlist.newproduct();
                    Sleep(600);
                    break;
                }
            case 2:
                {
                    mainlist.deleteproduct();
                    Sleep(600);
                    break;
                }
            case 3:
                {
                    mainlist.updateproduct();
                    Sleep(600);
                    break;
                }
            case 4:
                {
                    user disp;
                    disp.displayuser();
                    system("PAUSE");
                    break;
                }
            case 5:
                {
                    user ucount;
                    ucount.showcount();
                    system("PAUSE");
                    break;
                }
            case 6:
                {
                    cout<<"Signing out...";
                    Sleep(600);
                    break;
                }
            default:
                {
                    err;
                    Sleep(600);
                    break;
                }
            }
        }while(ch!=6);
    }
    else
    {
        cout<<"\n\nIncorrect username or password!\n";
        Sleep(600);
    }
}










int main()
{
    int ch;
    do
    {
        productlist mainlist;
        mainlist.extractfromfile();
        system("CLS");
        fflush(stdin);
        cout<<"1. Administrator\n2. User Login\n3. New User\n4. Logout\nEnter choice...";
        ch=num();
        switch(ch)
        {
        case 1:
            {
                char u[100];
                char p[100];
                cout<<"Enter username\t:\t";
                cin.getline(u,99);
                cout<<"Enter password\t:\t";
                cin.getline(p,99);
                admin mainadmin;
                mainadmin.modifyproductlist(u,p,mainlist);
                break;
            }
        case 2:
            {
                char u[100];
                char p[100];
                cout<<"Enter username\t:\t";
                cin.getline(u,100);
                cout<<"Enter password\t:\t";
                cin.getline(p,100);
                user mainuser;
                int check=mainuser.login(u,p);
                if(check==1)
                {
                    Sleep(800);
                    int ch1;
                    do
                    {
                        system("CLS");
                        cout<<"1. Products\n2. Update user details\n3. Delete user account\n4. Sign out\nEnter choice...";
                        ch1=num();
                        switch(ch1)
                        {
                        case 1:
                            {
                                int ch2;
                                do
                                {
                                    system("CLS");
                                    mainlist.displayproduct(mainuser.getcustage());
                                    cout<<"\n\n1. Add to cart\n2. Remove from cart\n3. Show cart\n4. Buy cart items\n5. Exit\nEnter choice...";
                                    ch2=num();
                                    switch(ch2)
                                    {
                                    case 1:
                                        {
                                            mainuser.cart.insertatbeg(mainlist.selectproduct());
                                            Sleep(600);
                                            break;
                                        }
                                    case 2:
                                        {
                                            mainuser.cart.del();
                                            Sleep(600);
                                            break;
                                        }
                                    case 3:
                                        {
                                            mainuser.cart.traverse();
                                            system("PAUSE");
                                            break;
                                        }
                                    case 4:
                                        {
                                            if(mainuser.cart.gettotal()==0)
                                            {
                                                ec;
                                                system("PAUSE");
                                            }
                                            else
                                            {
                                                cout<<"Total Price\t:\t"<<mainuser.cart.gettotal();
                                                cout<<"\nPAID!\n";
                                                mainuser.cart.emptylist();
                                                system("PAUSE");
                                            }

                                            break;
                                        }
                                    case 5:
                                        {
                                            cout<<"\n\nExiting...";
                                            Sleep(600);
                                            break;
                                        }
                                    default:
                                        {
                                            err;
                                            Sleep(600);
                                            break;
                                        }
                                    }
                                }while(ch2!=5);
                                break;
                            }
                        case 2:
                            {
                                mainuser.updateuser();
                                Sleep(600);
                                break;
                            }
                        case 3:
                            {
                                char con;
                                cout<<"\nConfirmation(y/n)...\n";
                                cin>>con;
                                if(con=='Y'||con=='y')
                                {
                                    mainuser.deleteuser();
                                    ch1=4;
                                }
                                Sleep(600);
                                break;
                            }
                        case 4:
                            {
                                cout<<"\n\nSigning out...\n";
                                Sleep(600);
                                break;
                            }
                        default:
                            {
                                err;
                                Sleep(600);
                                break;
                            }
                        }
                    }while(ch1!=4);
                }
            }
            Sleep(600);
            break;
        case 3:
            {
                user mainnew;
                mainnew.newuser();
                Sleep(600);
                break;
            }
        case 4:
            break;
        default:
            err;
            Sleep(600);
            break;
        }
    }while(ch!=4);
    return 0;
}




int num()
{
    int n=0,f=0;
    char p=getchar();
    while(p=='\n')
    {
        cout<<"Enter valid number=";
        p=getchar();
    }
    while(p!='\n')
    {
        if(p-'0'>=0&&p-'0'<=9)
        {
            n=n*10+(p-'0');
        }
        else
        {
            f=1;
        }
        p=getchar();
    }
    if(f==0)
        return n;
    else
    {
        cout<<"Enter valid number=";
        n=num();
        return n;
    }
}





float flo()
{
    int n=0,f=0,f1=0,dec=0;
    float x,m=0;
    char p=getchar();
    while(p=='\n')
    {
        cout<<"Enter valid number=";
        p=getchar();
    }
    while(p!='\n')
    {
        if(p-'0'>=0&&p-'0'<=9&&f1==0)
        {
            n=n*10+(p-'0');
        }
        else if(p=='.')
        {
            f1++;
        }
        else if(p-'0'>=0&&p-'0'<=9&&f1==1)
        {
            dec++;
            m=m*10+(p-'0');
        }
        else
        {
            f=1;
        }
        p=getchar();
    }
    if(f==0)
    {
        x=n+m/pow(10,dec);
        return x;
    }
    else
    {
        cout<<"Enter valid number=";
        x=flo();
        return x;
    }
}


void hello()
{
    cout<<"WELCOME\n\nProject by:-\nC022\tIsha Gupta\nC029\tAngad Singh Kataria\n";
    system("PAUSE");
}


void bye()
{
    system("CLS");
    remove("temp.dat");
    cout<<"\n\nTHANK YOU FOR VISITING!\n\nProject by:-\nC022\tIsha Gupta\nC029\tAngad Singh Kataria\n";
    system("PAUSE");
}
