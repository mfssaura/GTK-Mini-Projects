#include<gtk/gtk.h>
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdint.h>
#include <algorithm>

using namespace std;

int ch,i_del;

struct bookgui
{
    static int count;
    std::string bookName;
    std::string author;
    std::string edition;
    std::string type;
    std::string subtype;
    std::string serialNo;
    std::string book_price;

    bookgui():bookName(""),author(""),edition(""),type(""),subtype(""),serialNo(""),book_price(""){}

    bookgui(std::string const& bookName, std::string const& author, std::string const& edition, std::string const& type, std::string const& subtype,
            std::string const& serialNo,std::string const& book_price)
        : bookName(bookName),author(author),edition(edition),type(type),subtype(subtype),serialNo(serialNo),book_price(book_price){}

}cnt,data[100];

//char temp_label[200];
std::string temp_book_details;



struct base_main
{
    GtkWidget* window;
    GtkWidget* table;
    GtkWidget* insert_button;
    GtkWidget* search_button;
   // GtkWidget* delete_button;
   // GtkWidget* modify_button;
    GtkWidget *combo_box;
    GtkWidget* entry;
    GList *glist;
};

struct insert_new
{
    GtkWidget* window,*table,*b_name,*b_author,*b_edition,*b_type,*b_subtype,*b_serial_num,*b_price,*save,*random_button; // entries and buttons
    GtkWidget *l1,*l2,*l3,*l4,*l5,*l6,*l7,*frame;
};

struct modify
{
    GtkWidget* window,*bookname,*author,*edition,*type,*subtype,*serial_num,*table,*price,*save_change;
};
struct search_book
{
    GtkWidget *window,* table,*frame,*edit_button,*delete_button,*label;
    int no_of_entries;
};
struct edit_book
{
    GtkWidget* window,*e_table,*e_name,*e_author,*e_edition,*e_type,*e_subtype,*e_serial_num,*e_price,*e_save;
    GtkWidget *l1,*l2,*l3,*l4,*l5,*l6,*l7;
};

search_book *s;
edit_book *e;

bool comp1(bookgui const&,bookgui const&);
bool comp2(bookgui const&,bookgui const&);
bool comp3(bookgui const&,bookgui const&);
bool comp4(bookgui const&,bookgui const&);
bool comp5(bookgui const&,bookgui const&);
bool comp6(bookgui const&,bookgui const&);
bool comp7(bookgui const&,bookgui const&);

void member_details_save();
void member_dimensions_file();
void search_in_bookstore();
void delete_in_bookstore(GtkWidget*,gpointer);
GtkWidget* new_window();
struct base_main* initialize_base();
struct insert_new* initialize_insert(GtkWidget*);
void search_in_gtk();
void edit_in_bookstore(GtkWidget*,gpointer);
void modify_record(GtkWidget*,gpointer);


base_main *b;
insert_new *in;


int bookgui::count=0;

bool comp1(bookgui const & a,bookgui const & b)
{
    return(a.bookName<b.bookName);
}

bool comp2(bookgui const & a,bookgui const & b)
{
    return(a.author<b.author);
}

bool comp3(bookgui const & a,bookgui const & b)
{
    return(a.edition<b.edition);
}

bool comp4(bookgui const & a,bookgui const & b)
{
    return(a.type<b.type);
}

bool comp5(bookgui const & a,bookgui const & b)
{
    return(a.subtype<b.subtype);
}

bool comp6(bookgui const & a,bookgui const & b)
{
    return(a.serialNo<b.serialNo);
}

bool comp7(bookgui const & a,bookgui const & b)
{
    return(a.book_price<b.book_price);
}

void gen_random()
{
    char *s=(char *)malloc(13*sizeof(char));
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 11; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[11] = 0;
    gtk_label_set_text(GTK_LABEL(in->b_serial_num),s);
    return;
}


void member_details_save()
{
    int	i=cnt.count;
    std::string	filePath;

    const char* temp=gtk_entry_get_text(GTK_ENTRY(in->b_name));
    std::string t_name(temp);
    cout <<t_name;
    std::transform(t_name.begin(),t_name.end(),t_name.begin(),::tolower);

    temp=gtk_entry_get_text(GTK_ENTRY(in->b_author));
    std::string t_author(temp);
    cout << t_author;
    std::transform(t_author.begin(), t_author.end(), t_author.begin(), ::tolower);

    temp=gtk_entry_get_text(GTK_ENTRY(in->b_edition));
    std::string t_edition(temp);
    std::transform(t_edition.begin(), t_edition.end(), t_edition.begin(), ::tolower);

    temp=gtk_entry_get_text(GTK_ENTRY(in->b_type));
    std::string t_type(temp);
    std::transform(t_type.begin(), t_type.end(), t_type.begin(), ::tolower);

    temp=gtk_entry_get_text(GTK_ENTRY(in->b_subtype));
    std::string t_subtype(temp);
    std::transform(t_subtype.begin(), t_subtype.end(), t_subtype.begin(), ::tolower);

    temp=gtk_entry_get_text(GTK_ENTRY(in->b_price));
    std::string t_price(temp);
    std::transform(t_price.begin(), t_price.end(), t_price.begin(), ::tolower);

     temp=gtk_label_get_text(GTK_LABEL(in->b_serial_num));
    std::string t_serial(temp);
    std::transform(t_serial.begin(), t_serial.end(), t_serial.begin(), ::tolower);



    data[i].bookName=t_name;
   
    data[i].author=t_author;
   
    data[i].edition=t_edition;
   
    data[i].type=t_type;
   
    data[i].subtype=t_subtype;
   
    data[i].serialNo=t_serial;

    data[i].book_price=t_price;
   

    ofstream  dimensionsOutfile;
    dimensionsOutfile.open ("test.dat",ofstream::in | ofstream::out | ofstream::binary | ofstream::ate | ofstream::app);
    if (!dimensionsOutfile)
    {
        cout<<"Cannot load file"<<endl;
        return ;
    }
    else
    {

        dimensionsOutfile<< data[i].bookName << "\n"
            << data[i].author << "\n" << data[i].edition << "\n"
            << data[i].type << "\n" << data[i].subtype << "\n"
            << data[i].book_price << "\n" << data[i].serialNo << "\n";
        cout <<"\nMember has been successfully saved"<<endl<<endl<<endl;
        dimensionsOutfile.close();
    }
    cnt.count++;
    gtk_widget_destroy(in->window);
    return;
}

void destroy_delete(GtkWidget* widget)
{
    gtk_widget_destroy(s->window);
}

void search_in_bookstore()
{
    int i,row_initial=0,row_final=1,col_initial=1,col_final=2;
    cnt.count=0;
    int flag=0;


     const gchar *str;
     str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (b->combo_box)->entry));
     if(strcmp(str,"Book Name")==0)
        ch=1;
     else if(strcmp(str,"Author")==0)
         ch=2;
      else if(strcmp(str,"Edition")==0)
         ch=3;
      else if(strcmp(str,"Type")==0)
         ch=4;
     else if(strcmp(str,"Subtype")==0)
         ch=5;
     else if(strcmp(str,"Price")==0)
         ch=6;
     else if(strcmp(str,"Serial Number")==0)
         ch=7; 
     else
         ch=1;

    cout << ch;

     s=(search_book *)malloc(sizeof(search_book));
    s->window=new_window();
    gtk_widget_set_size_request(s->window,800,800);
    s->table=gtk_table_new(10,7,TRUE);
    gtk_container_add(GTK_CONTAINER(s->window),s->table);
    gtk_table_set_row_spacings(GTK_TABLE(s->table),5);
    gtk_table_set_col_spacings(GTK_TABLE(s->table),10);
    gtk_widget_show(s->table);
    gtk_widget_show(s->window);



   const char* temp=gtk_entry_get_text(GTK_ENTRY(b->entry));
    std::string temp_str(temp);

    std::transform(temp_str.begin(), temp_str.end(), temp_str.begin(), ::tolower);

    ifstream  dimensionsInFile;
    dimensionsInFile.open ("test.dat");
    if (!dimensionsInFile)
    {
        cout<<"Cannot load file"<<endl;
        return ;
    }
    else
    {
        for (i=0; dimensionsInFile>> data[i].bookName
                >> data[i].author >> data[i].edition
                >> data[i].type >> data[i].subtype
                >> data[i].book_price >> data[i].serialNo; i++);
        i_del=i;

        dimensionsInFile.close();

        if(ch==1)
        {
            sort(data,data+i,comp1);
            for(int j=0 ; j<i ; j++)
            {
                if(data[j].bookName==temp_str)
                {
                    flag++;
                    cout << "Name: "<< data[j].bookName << endl;
                    cout << "Author: "<< data[j].author << endl;
                    cout << "Edition: "<< data[j].edition << endl;
                    cout << "Type: "<< data[j].type << endl;
                    cout << "Subtype: "<< data[j].subtype << endl;
                    cout << "SerialNo: "<< data[j].serialNo << endl;
                    cout << "Price: "<< data[j].book_price << endl<<endl<<endl;
                    temp_book_details=data[j].bookName+"\n\n"+data[j].author+"\n\n"+data[j].edition+"\n\n"+data[j].type+"\n\n"+data[j].subtype+"\n\n"+data[j].book_price+"\n\n"+data[j].serialNo; 
                     std::transform(temp_book_details.begin(), temp_book_details.end(), temp_book_details.begin(), ::toupper);
                    const char* temp_label=temp_book_details.c_str();

                    s->frame=gtk_frame_new("");
                    s->label=gtk_label_new(temp_label);
                    gtk_container_add(GTK_CONTAINER(s->frame),s->label);
                    gtk_widget_show(s->label);
                    s->edit_button=gtk_button_new_with_label("EDIT");
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    gtk_widget_show(s->edit_button);
                    gtk_widget_show(s->delete_button);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(delete_in_bookstore),(gpointer)j);

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                
                }  
            }
        }
        else if(ch==2)
        {
            sort(data,data+i,comp2);
            for(int j=0 ; j<i ; j++)
            {
                if(data[j].author==temp_str)
                {
                    flag++;
                    cout << "Name: "<< data[j].bookName << endl;
                    cout << "Author: "<< data[j].author << endl;
                    cout << "Edition: "<< data[j].edition << endl;
                    cout << "Type: "<< data[j].type << endl;
                    cout << "Subtype: "<< data[j].subtype << endl;
                    cout << "SerialNo: "<< data[j].serialNo << endl;
                    cout << "Price: "<< data[j].book_price << endl<<endl<<endl;
                    temp_book_details=data[j].bookName+"\n\n"+data[j].author+"\n\n"+data[j].edition+"\n\n"+data[j].type+"\n\n"+data[j].subtype+"\n\n"+data[j].book_price+"\n\n"+data[j].serialNo; 
                      std::transform(temp_book_details.begin(), temp_book_details.end(), temp_book_details.begin(), ::toupper);
                    const char* temp_label=temp_book_details.c_str();

                    s->frame=gtk_frame_new("");
                    s->label=gtk_label_new(temp_label);
                    gtk_container_add(GTK_CONTAINER(s->frame),s->label);
                    gtk_widget_show(s->label);
                    s->edit_button=gtk_button_new_with_label("EDIT");
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    gtk_widget_show(s->edit_button);
                    gtk_widget_show(s->delete_button);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(delete_in_bookstore),(gpointer)j);

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                }
              
            }
        }
        else if(ch==3)
        {
            sort(data,data+i,comp3);
            for(int j=0 ; j<i ; j++)
            {
                if(data[j].edition==temp_str)
                {
                    flag++;
                    cout << "Name: "<< data[j].bookName << endl;
                    cout << "Author: "<< data[j].author << endl;
                    cout << "Edition: "<< data[j].edition << endl;
                    cout << "Type: "<< data[j].type << endl;
                    cout << "Subtype: "<< data[j].subtype << endl;
                    cout << "SerialNo: "<< data[j].serialNo << endl;
                    cout << "Price: "<< data[j].book_price << endl<<endl<<endl;
                   temp_book_details=data[j].bookName+"\n\n"+data[j].author+"\n\n"+data[j].edition+"\n\n"+data[j].type+"\n\n"+data[j].subtype+"\n\n"+data[j].book_price+"\n\n"+data[j].serialNo; 
                     std::transform(temp_book_details.begin(), temp_book_details.end(), temp_book_details.begin(), ::toupper);
                    const char* temp_label=temp_book_details.c_str();

                    s->frame=gtk_frame_new("");
                    s->label=gtk_label_new(temp_label);
                    gtk_container_add(GTK_CONTAINER(s->frame),s->label);
                    gtk_widget_show(s->label);
                    s->edit_button=gtk_button_new_with_label("EDIT");
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    gtk_widget_show(s->edit_button);
                    gtk_widget_show(s->delete_button);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(delete_in_bookstore),(gpointer)j);

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                }
             
            }
        }
        else if(ch==4)
        {
            sort(data,data+i,comp4);
            for(int j=0 ; j<i ; j++)
            {
                if(data[j].type==temp_str)
                {
                    flag++;
                    cout << "Name: "<< data[j].bookName << endl;
                    cout << "Author: "<< data[j].author << endl;
                    cout << "Edition: "<< data[j].edition << endl;
                    cout << "Type: "<< data[j].type << endl;
                    cout << "Subtype: "<< data[j].subtype << endl;
                    cout << "SerialNo: "<< data[j].serialNo << endl;
                    cout << "Price: "<< data[j].book_price << endl<<endl<<endl;
                   temp_book_details=data[j].bookName+"\n\n"+data[j].author+"\n\n"+data[j].edition+"\n\n"+data[j].type+"\n\n"+data[j].subtype+"\n\n"+data[j].book_price+"\n\n"+data[j].serialNo; 
                     std::transform(temp_book_details.begin(), temp_book_details.end(), temp_book_details.begin(), ::toupper);
                    const char* temp_label=temp_book_details.c_str();

                    s->frame=gtk_frame_new("");
                    s->label=gtk_label_new(temp_label);
                    gtk_container_add(GTK_CONTAINER(s->frame),s->label);
                    gtk_widget_show(s->label);
                    s->edit_button=gtk_button_new_with_label("EDIT");
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    gtk_widget_show(s->edit_button);
                    gtk_widget_show(s->delete_button);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(delete_in_bookstore),(gpointer)j);

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                }
            }
        }
        else if(ch==5)
        {
            sort(data,data+i,comp5);
            for(int j=0 ; j<i ; j++)
            {
                if(data[j].subtype==temp_str)
                {
                    flag++;
                    cout << "Name: "<< data[j].bookName << endl;
                    cout << "Author: "<< data[j].author << endl;
                    cout << "Edition: "<< data[j].edition << endl;
                    cout << "Type: "<< data[j].type << endl;
                    cout << "Subtype: "<< data[j].subtype << endl;
                    cout << "SerialNo: "<< data[j].serialNo << endl;
                    cout << "Price: "<< data[j].book_price << endl<<endl<<endl;
                   temp_book_details=data[j].bookName+"\n\n"+data[j].author+"\n\n"+data[j].edition+"\n\n"+data[j].type+"\n\n"+data[j].subtype+"\n\n"+data[j].book_price+"\n\n"+data[j].serialNo; 
                     std::transform(temp_book_details.begin(), temp_book_details.end(), temp_book_details.begin(), ::toupper); 
                   const char* temp_label=temp_book_details.c_str();

                    s->frame=gtk_frame_new("");
                    s->label=gtk_label_new(temp_label);
                    gtk_container_add(GTK_CONTAINER(s->frame),s->label);
                    gtk_widget_show(s->label);
                    s->edit_button=gtk_button_new_with_label("EDIT");
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    gtk_widget_show(s->edit_button);
                    gtk_widget_show(s->delete_button);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(delete_in_bookstore),(gpointer)j);

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                }
            }
        }
        else if(ch==6)
        {
            sort(data,data+i,comp6);
            for(int j=0 ; j<i ; j++)
            {
                if(data[j].serialNo==temp_str)
                {
                    flag++;
                    cout << "Name: "<< data[j].bookName << endl;
                    cout << "Author: "<< data[j].author << endl;
                    cout << "Edition: "<< data[j].edition << endl;
                    cout << "Type: "<< data[j].type << endl;
                    cout << "Subtype: "<< data[j].subtype << endl;
                    cout << "SerialNo: "<< data[j].serialNo << endl;
                    cout << "Price: "<< data[j].book_price << endl<<endl<<endl;
                   temp_book_details=data[j].bookName+"\n\n"+data[j].author+"\n\n"+data[j].edition+"\n\n"+data[j].type+"\n\n"+data[j].subtype+"\n\n"+data[j].book_price+"\n\n"+data[j].serialNo; 
                    std::transform(temp_book_details.begin(), temp_book_details.end(), temp_book_details.begin(), ::toupper); 
                   const char* temp_label=temp_book_details.c_str();

                    s->frame=gtk_frame_new("");
                    s->label=gtk_label_new(temp_label);
                    gtk_container_add(GTK_CONTAINER(s->frame),s->label);
                    gtk_widget_show(s->label);
                    s->edit_button=gtk_button_new_with_label("EDIT");
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    gtk_widget_show(s->edit_button);
                    gtk_widget_show(s->delete_button);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(delete_in_bookstore),(gpointer)j);

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                }
            }
        }
        else if(ch==7)
        {
            sort(data,data+i,comp7);
            for(int j=0 ; j<i ; j++)
            {
                if(data[j].book_price==temp_str)
                {
                    flag++;
                    cout << "Name: "<< data[j].bookName << endl;
                    cout << "Author: "<< data[j].author << endl;
                    cout << "Edition: "<< data[j].edition << endl;
                    cout << "Type: "<< data[j].type << endl;
                    cout << "Subtype: "<< data[j].subtype << endl;
                    cout << "SerialNo: "<< data[j].serialNo << endl;
                    cout << "Price: "<< data[j].book_price << endl<<endl<<endl;
                   temp_book_details=data[j].bookName+"\n\n"+data[j].author+"\n\n"+data[j].edition+"\n\n"+data[j].type+"\n\n"+data[j].subtype+"\n"+data[j].serialNo+"\n\n"+data[j].book_price; 
                     std::transform(temp_book_details.begin(), temp_book_details.end(), temp_book_details.begin(), ::toupper); 
                   const char* temp_label=temp_book_details.c_str();

                    s->frame=gtk_frame_new("");
                    s->label=gtk_label_new(temp_label);
                    gtk_container_add(GTK_CONTAINER(s->frame),s->label);
                    gtk_widget_show(s->label);
                    s->edit_button=gtk_button_new_with_label("EDIT");
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    gtk_widget_show(s->edit_button);
                    gtk_widget_show(s->delete_button);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(delete_in_bookstore),(gpointer)j);

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                }        
            }
        }
       
    }
    if(flag==0)
    {
        GtkWidget* b=gtk_button_new_with_label("Click to close");
         GtkWidget* name=gtk_label_new("NO  RESULT  FOUND!");
         gtk_widget_show(name);
         gtk_widget_show(b);
         gtk_table_attach_defaults(GTK_TABLE(s->table),name,2,5,4,5);
         gtk_table_attach_defaults(GTK_TABLE(s->table),b,5,8,4,5);
         gtk_signal_connect(GTK_OBJECT(b),"clicked",GTK_SIGNAL_FUNC(destroy_delete),NULL);
    }    
   
    cout<<"Moving out of search function\n\n";
}

void delete_in_bookstore(GtkWidget* widget,gpointer row)
{

   int index=(uintptr_t)row;

    cout<<index<<endl;

    data[index].bookName=data[index].author=data[index].edition=data[index].type=data[index].subtype="*****";
    data[index].serialNo=-1;
    data[index].book_price=-1;

    cout<<"Changed the record into data[]\n";

    ofstream  dimensionsOutfile;
    dimensionsOutfile.open ("test.dat");

    if (!dimensionsOutfile)
    {
        cout<<"Cannot load file"<<endl;
        return;
    }
    else
    {
        cout<<"Starting to delete\n";
        for(int j=0;j<i_del;j++)
        {
            if(data[j].bookName!="*****")
            {
                dimensionsOutfile<< data[j].bookName << "\n"
                    << data[j].author << "\n" << data[j].edition << "\n"
                    << data[j].type << "\n" << data[j].subtype << "\n"
                    << data[j].book_price << "\n" << data[j].serialNo << "\n";
            }
        }
        cout <<"\nMember has been successfully deleted..!!"<<endl<<endl<<endl;
        dimensionsOutfile.close();
    }
    
}

void modify_record(GtkWidget* widget,gpointer row)
{
    int ind=(uintptr_t)row;

    cout<<"Moving inside modify_record";

    cout<<ind<<endl;

    const char* temp=gtk_entry_get_text(GTK_ENTRY(e->e_name));
    std::string t_name(temp);
    std::transform(t_name.begin(),t_name.end(),t_name.begin(),::tolower);
    data[ind].bookName=t_name;


    temp=gtk_entry_get_text(GTK_ENTRY(e->e_author));
    std::string t_author(temp);
    std::transform(t_name.begin(),t_name.end(),t_name.begin(),::tolower);
    data[ind].author=t_author;


    temp=gtk_entry_get_text(GTK_ENTRY(e->e_edition));
    std::string t_edition(temp);
    std::transform(t_name.begin(),t_name.end(),t_name.begin(),::tolower);
    data[ind].edition=t_edition;


    temp=gtk_entry_get_text(GTK_ENTRY(e->e_type));
    std::string t_type(temp);
    std::transform(t_name.begin(),t_name.end(),t_name.begin(),::tolower);
    data[ind].type=t_type;


    temp=gtk_entry_get_text(GTK_ENTRY(e->e_subtype));
    std::string t_subtype(temp);
    std::transform(t_name.begin(),t_name.end(),t_name.begin(),::tolower);
    data[ind].subtype=t_subtype;


    temp=gtk_entry_get_text(GTK_ENTRY(e->e_price));
    std::string t_price(temp);
    std::transform(t_name.begin(),t_name.end(),t_name.begin(),::tolower);
    data[ind].book_price=t_price;


    temp=gtk_label_get_text(GTK_LABEL(e->e_serial_num));
    std::string t_serial(temp);
    std::transform(t_name.begin(),t_name.end(),t_name.begin(),::tolower);
    data[ind].serialNo=t_serial;

    cout<<"completed writing changes";


    ofstream  dimensionsOutfile;
    dimensionsOutfile.open ("test.dat");

    if (!dimensionsOutfile)
    {
        cout<<"Cannot load file"<<endl;
        return;
    }
    else
    {
        for(int j=0;j<i_del;j++)
        {
            dimensionsOutfile<< data[j].bookName << "\n"
                << data[j].author << "\n" << data[j].edition << "\n"
                << data[j].type << "\n" << data[j].subtype << "\n"
                << data[j].book_price << "\n" << data[j].serialNo << "\n" ;
        }
        cout <<"\nMember has been successfully modified..!!"<<endl<<endl<<endl;
        dimensionsOutfile.close();
    }
    gtk_widget_destroy(e->window);
}



void edit_in_bookstore(GtkWidget* widget,gpointer row)
{
    int index=(uintptr_t)row;

    cout<<"Entered into edit_in_bookstore";

    e=(edit_book *)malloc(sizeof(edit_book));

    e->window=new_window();

    e->e_table=gtk_table_new(8,2,TRUE);
    gtk_container_add(GTK_CONTAINER(e->window),e->e_table);

    e->e_name=gtk_entry_new();
    e->e_author=gtk_entry_new();
    e->e_price=gtk_entry_new();
    e->e_edition=gtk_entry_new();
    e->e_type=gtk_entry_new();
    e->e_subtype=gtk_entry_new();
    e->e_serial_num=gtk_label_new("");

    e->l1=gtk_label_new("Name");
    e->l2=gtk_label_new("Author");
    e->l3=gtk_label_new("Edition");
    e->l4=gtk_label_new("Type");
    e->l5=gtk_label_new("Subtype");
    e->l6=gtk_label_new("Price");
    e->l7=gtk_label_new("Serial");

    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->l1,0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->l2,0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->l3,0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->l4,0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->l5,0,1,4,5);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->l6,0,1,5,6);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->l7,0,1,6,7);

    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->e_name,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->e_author,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->e_edition,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->e_type,1,2,3,4);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->e_subtype,1,2,4,5);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->e_price,1,2,5,6);
    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->e_serial_num,1,2,6,7);

    const char* temp=(data[index].bookName).c_str();
    gtk_entry_set_text(GTK_ENTRY(e->e_name),temp);

    temp=(data[index].author).c_str();
    gtk_entry_set_text(GTK_ENTRY(e->e_author),temp);

    temp=(data[index].edition).c_str();
    gtk_entry_set_text(GTK_ENTRY(e->e_edition),temp);

    temp=(data[index].type).c_str();
    gtk_entry_set_text(GTK_ENTRY(e->e_type),temp);

    temp=(data[index].subtype).c_str();
    gtk_entry_set_text(GTK_ENTRY(e->e_subtype),temp);

    temp=(data[index].book_price).c_str();
    gtk_entry_set_text(GTK_ENTRY(e->e_price),temp);

    temp=(data[index].serialNo).c_str();
    gtk_label_set_text(GTK_LABEL(e->e_serial_num),temp);

     e->e_save=gtk_button_new_with_label("Save");
    gtk_signal_connect(GTK_OBJECT(e->e_save),"clicked",GTK_SIGNAL_FUNC(modify_record),(gpointer)index);

    gtk_table_attach_defaults(GTK_TABLE(e->e_table),e->e_save,1,2,7,8);

    gtk_widget_show_all(e->window);
}



GtkWidget* new_window()
{
    GtkWidget *window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window,600,600);
    gtk_container_set_border_width(GTK_CONTAINER(window), 30);
    gtk_window_set_title(GTK_WINDOW(window),"DIGITAL LIBRARY");
    return window;
}



base_main* initialize_base()
{
    GtkWidget* image1 = gtk_image_new_from_file ("insert.png");
    GtkWidget* image2 = gtk_image_new_from_file ("search.png");
    GtkWidget* image3 = gtk_image_new_from_file ("db_name.png");
   // GtkWidget *image4=gtk_image_new_from_file("delete.png");

    b=(base_main*)malloc(sizeof(base_main));
    b->window=new_window();
    gtk_signal_connect(GTK_OBJECT(b->window),"destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
    b->table=gtk_table_new(7,3,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(b->table),20);
    gtk_table_set_col_spacings(GTK_TABLE(b->table),20);
    b->entry=gtk_entry_new();
    b->insert_button=gtk_button_new();
    b->search_button=gtk_button_new();
   // b->delete_button=gtk_button_new();
    b->combo_box=gtk_combo_new();  // combo box
    b->glist=NULL;
    b->glist = g_list_append(b->glist,(gpointer) "Book Name");
    b->glist = g_list_append(b->glist,(gpointer) "Author");
    b->glist = g_list_append(b->glist,(gpointer) "Edition"); 
    b->glist = g_list_append(b->glist,(gpointer) "Type");
    b->glist = g_list_append(b->glist,(gpointer) "Subtype");
    b->glist = g_list_append(b->glist,(gpointer) "Price");
    b->glist = g_list_append(b->glist,(gpointer) "Serial Number");
    gtk_combo_set_popdown_strings( GTK_COMBO(b->combo_box), b->glist) ;


    GdkColor black,blue;
    gdk_color_parse("#DEB887",&black);
    gdk_color_parse("black",&blue);
    gtk_widget_modify_bg(b->window, GTK_STATE_NORMAL, &black);


    gtk_container_add(GTK_CONTAINER(b->insert_button),image1);
     gtk_container_add(GTK_CONTAINER(b->search_button),image2);
   //gtk_container_add(GTK_CONTAINER(b->delete_button),image4);
    gtk_signal_connect(GTK_OBJECT(b->insert_button),"clicked",GTK_SIGNAL_FUNC(initialize_insert),NULL);
    

    gtk_container_add(GTK_CONTAINER(b->window),b->table);

    gtk_table_attach_defaults(GTK_TABLE(b->table),image3,0,3,0,1);

    gtk_table_attach_defaults(GTK_TABLE(b->table),b->insert_button,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(b->table),b->entry,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(b->table),b->combo_box,2,3,2,3);
    gtk_table_attach_defaults(GTK_TABLE(b->table),b->search_button,1,2,3,4);
  //  gtk_table_attach_defaults(GTK_TABLE(b->table),b->delete_button,0,1,2,3);
    gtk_signal_connect(GTK_OBJECT(b->search_button),"clicked",GTK_SIGNAL_FUNC(search_in_bookstore),NULL);
   // gtk_signal_connect(GTK_OBJECT(b->delete_button),"clicked",GTK_SIGNAL_FUNC(delete_in_bookstore),NULL);
    gtk_widget_show_all(b->window);

    return b;
}

insert_new* initialize_insert(GtkWidget* button)
{
    in=(insert_new *)malloc(sizeof(insert_new));
    in->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(in->window,400,400);
    gtk_container_set_border_width(GTK_CONTAINER(in->window), 20);
    gtk_window_set_title(GTK_WINDOW(in->window),"INSERT");

    in->table=gtk_table_new(10,2,TRUE);
    gtk_container_add(GTK_CONTAINER(in->window),in->table);
    gtk_table_set_row_spacings(GTK_TABLE(in->table),10);

    in->b_name=gtk_entry_new();
    in->b_author=gtk_entry_new();
    in->b_price=gtk_entry_new();
    in->b_edition=gtk_entry_new();
    in->b_type=gtk_entry_new();
    in->b_subtype=gtk_entry_new();
    in->frame=gtk_frame_new("");
    in->b_serial_num=gtk_label_new("");
    in->random_button=gtk_button_new_with_label("generate");
    gtk_container_add(GTK_CONTAINER(in->frame),in->b_serial_num);
    gtk_signal_connect(GTK_OBJECT(in->random_button),"clicked",GTK_SIGNAL_FUNC(gen_random),NULL);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->random_button,1,2,7,8);

    in->l1=gtk_label_new("Name");
    in->l2=gtk_label_new("Author");
    in->l3=gtk_label_new("Edition");
    in->l4=gtk_label_new("Type");
    in->l5=gtk_label_new("Subtype");
    in->l6=gtk_label_new("Price");
    in->l7=gtk_label_new("Serial");

    gtk_table_attach_defaults(GTK_TABLE(in->table),in->l1,0,1,0,1);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->l2,0,1,1,2);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->l3,0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->l4,0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->l5,0,1,4,5);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->l6,0,1,5,6);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->l7,0,1,6,7);

    gtk_table_attach_defaults(GTK_TABLE(in->table),in->b_name,1,2,0,1);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->b_author,1,2,1,2);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->b_edition,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->b_type,1,2,3,4);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->b_subtype,1,2,4,5);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->b_price,1,2,5,6);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->frame,1,2,6,7);

    in->save=gtk_button_new_with_label("Save");
    gtk_signal_connect(GTK_OBJECT(in->save),"clicked",GTK_SIGNAL_FUNC(member_details_save),NULL);

    gtk_table_attach_defaults(GTK_TABLE(in->table),in->save,1,2,9,10);

    cout<<"After inserting into file";

    gtk_widget_show_all(in->window);
}

int main(int argc,char* argv[])
{
    cnt.count=0;

    gtk_init(&argc,&argv)ase();

    gtk_main();;

    base_main* b=initialize_b

    return 0;
}
