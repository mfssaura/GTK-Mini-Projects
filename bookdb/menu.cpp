#include<iostream>
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <gtk/gtk.h>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <algorithm>

using namespace std;

struct bookgui
{
    int count;
    std::string bookName;
    std::string author;
    std::string edition;
    std::string type;
    std::string subtype;
    std::string serialNo;
    std::string book_price;

bookgui():bookName(""),author(""),edition(""),type(""),subtype(""),serialNo(""),book_price(""){}

bookgui(std::string const& bookName, std::string const& author, std::string const& edition, std::string const& type, std::string const& subtype,std::string const& serialNo,std::string const& book_price)
        : bookName(bookName),author(author),edition(edition),type(type),subtype(subtype),serialNo(serialNo),book_price(book_price){}
}cnt,data[100];

typedef struct insert_new
{
GtkWidget* window,*table,*entry,*search_button,*combo_box,*b_name,*b_author,*b_edition,*b_type,*b_subtype,*b_serial_num,*b_price,*save,
*random_button; // entries and buttons
GtkWidget *l1,*l2,*l3,*l4,*l5,*l6,*l7,*frame;
GList *glist;
}insert_new;

insert_new *in;

struct search_book
{
    GtkWidget *window,* table,*frame,*edit_button,*delete_button,*label;
    int no_of_entries;
};
search_book *s;

struct edit_book
{
    GtkWidget* window,*e_table,*e_name,*e_author,*e_edition,*e_type,*e_subtype,*e_serial_num,*e_price,*e_save;
    GtkWidget *l1,*l2,*l3,*l4,*l5,*l6,*l7;
};
edit_book *e;

int ch,i_del;
std::string temp_book_details;
int count=0;

static void s1_in_bookstore(gchar *);
void _search1();
static void s2_in_bookstore(gchar *);
void _search2();
static void s3_in_bookstore(gchar *);
void _search3();
static void s4_in_bookstore(gchar *);
void _search4();
static void s5_in_bookstore(gchar *);
void _search5();
static void s6_in_bookstore(gchar *);
void _search6();
static gint button_press (GtkWidget *, GdkEvent *);
static void menuitem_response (gchar *);
void gen_random();
void member_details_save();
void destroy_delete(GtkWidget* widget);
static void delete_in_bookstore(gchar *);
void search_in_bookstore();
void _search_in_bookstore();
void _delete(GtkWidget* widget,gpointer row);
void edit_in_bookstore(GtkWidget*,gpointer);
void modify_record(GtkWidget*,gpointer);
static void modify_in_bookstore(gchar *);

//main function
int main(int argc, char **argv)
{

    GtkWidget *window, *menubar, *root, *search, *help, *root_menu, *search_menu,*help_menu;
    GtkWidget *button;
    GtkWidget *r1, *r2, *r3, *s1,*s2,*s3,*s4,*s5,*s6, *contents, *about;
    char buf[128];
    int i;

    gtk_init (&argc, &argv);
    /* create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_usize (GTK_WIDGET (window), 400, 400);
    gtk_window_set_title (GTK_WINDOW (window), "DIGITAL LIBRARY STORE");
    gtk_signal_connect (GTK_OBJECT (window), "delete_event",(GtkSignalFunc) gtk_main_quit, NULL);

    /* Init the menu-widget, and remember -- never
     * gtk_show_widget() the menu widget!! 
     * This is the menu that holds the menu items, the one that
     * will pop up when you click on the "Root Menu" in the app */

menubar = gtk_menu_bar_new ();
root = gtk_menu_item_new_with_label ("Root Menu");
search = gtk_menu_item_new_with_label ("Search By");
help = gtk_menu_item_new_with_label ("Help");

root_menu = gtk_menu_new ();
search_menu = gtk_menu_new ();
help_menu = gtk_menu_new ();

gtk_menu_item_set_submenu (GTK_MENU_ITEM (root), root_menu);
gtk_menu_item_set_submenu (GTK_MENU_ITEM (search), search_menu);
gtk_menu_item_set_submenu (GTK_MENU_ITEM (help), help_menu);
gtk_menu_shell_append (GTK_MENU_SHELL (menubar), root);
gtk_menu_shell_append (GTK_MENU_SHELL (menubar), search);
gtk_menu_shell_append (GTK_MENU_SHELL (menubar), help);
/* Create the File menu content. */
sprintf (buf, "1-> %s", "BOOK INSERTION");
r1=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append(GTK_MENU_SHELL(root_menu), r1);
gtk_signal_connect_object (GTK_OBJECT (r1), "activate",GTK_SIGNAL_FUNC (menuitem_response), (gpointer) g_strdup (buf));
sprintf (buf, "2-> %s", "BOOK DELETION");
r2=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append(GTK_MENU_SHELL(root_menu), r2);
gtk_signal_connect_object (GTK_OBJECT (r2), "activate",GTK_SIGNAL_FUNC (delete_in_bookstore), (gpointer) g_strdup(buf));
sprintf (buf, "3-> %s", "BOOK MODIFICATION");
r3=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append(GTK_MENU_SHELL(root_menu), r3);
gtk_signal_connect_object (GTK_OBJECT (r3), "activate",GTK_SIGNAL_FUNC (modify_in_bookstore), (gpointer) g_strdup (buf));

/* Create the Edit menu content. */

sprintf (buf, "1-> %s", "SEARCH BY BOOK NAME");
s1=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append (GTK_MENU_SHELL (search_menu), s1);
gtk_signal_connect_object (GTK_OBJECT (s1), "activate",GTK_SIGNAL_FUNC (s1_in_bookstore), (gpointer) g_strdup (buf));


sprintf (buf, "2-> %s", "SEARCH BY AUTHOR");
s2=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append (GTK_MENU_SHELL (search_menu), s2);
gtk_signal_connect_object (GTK_OBJECT (s2), "activate",GTK_SIGNAL_FUNC (s2_in_bookstore), (gpointer) g_strdup (buf));

sprintf (buf, "3-> %s", "SEARCH BY EDITION");
s3=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append (GTK_MENU_SHELL (search_menu), s3);
gtk_signal_connect_object (GTK_OBJECT (s3), "activate",GTK_SIGNAL_FUNC (s3_in_bookstore), (gpointer) g_strdup (buf));

sprintf (buf, "4-> %s", "SEARCH BY TYPE");
s4=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append (GTK_MENU_SHELL (search_menu), s4);
gtk_signal_connect_object (GTK_OBJECT (s4), "activate",GTK_SIGNAL_FUNC (s4_in_bookstore), (gpointer) g_strdup (buf));

sprintf (buf, "5-> %s", "SEARCH BY SUBTYPE");
s5=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append (GTK_MENU_SHELL (search_menu), s5);
gtk_signal_connect_object (GTK_OBJECT (s5), "activate",GTK_SIGNAL_FUNC (s5_in_bookstore), (gpointer) g_strdup (buf));

sprintf (buf, "6-> %s", "SEARCH BY PRICE");
s6=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append (GTK_MENU_SHELL (search_menu), s6);
gtk_signal_connect_object (GTK_OBJECT (s6), "activate",GTK_SIGNAL_FUNC (s6_in_bookstore), (gpointer) g_strdup (buf));



/* Create the Help menu content. */
sprintf (buf, "1- %s", "CONTENTS");
contents=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append (GTK_MENU_SHELL (help_menu), contents);


sprintf (buf, "1- %s", "ABOUT");
about=gtk_menu_item_new_with_label (buf);
gtk_menu_shell_append (GTK_MENU_SHELL (help_menu), about);
gtk_container_add (GTK_CONTAINER (window), menubar);

gtk_widget_show_all (window);

gtk_main ();

return(0);
}


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

/* Respond to a button-press by posting a menu passed in as widget.
 *

/* Respond to a button-press by posting a menu passed in as widget.
 *
 * Note that the "widget" argument is the menu being posted, NOT
 * the button that was pressed.
 */


/*Do something when a menu item is selected */

static void menuitem_response(gchar *string )
{

    in=(insert_new *)malloc(sizeof(insert_new));
    in->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(in->window,400,400);
    gtk_container_set_border_width(GTK_CONTAINER(in->window), 5);
    gtk_window_set_title(GTK_WINDOW(in->window),"INSERT");

    in->table=gtk_table_new(10,2,TRUE);
    gtk_container_add(GTK_CONTAINER(in->window),in->table);
    gtk_table_set_row_spacings(GTK_TABLE(in->table),5);

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
    in->l7=gtk_label_new("Serial No");

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

    gtk_widget_show_all(in->window);

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


void destroy_delete(GtkWidget* widget)
{
    gtk_widget_destroy(s->window);
}

static void delete_in_bookstore(gchar *string)
{

    in=(insert_new *)malloc(sizeof(insert_new));
    in->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(in->window,400,400);
    gtk_container_set_border_width(GTK_CONTAINER(in->window), 5);
    gtk_window_set_title(GTK_WINDOW(in->window),"DELETE");
    

    in->table=gtk_table_new(7,3,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(in->table),20);
    gtk_table_set_col_spacings(GTK_TABLE(in->table),20);
    in->entry=gtk_entry_new();
    in->search_button=gtk_button_new_with_label("DELETE");

    in->combo_box=gtk_combo_new();  
    in->glist=NULL;
    in->glist = g_list_append(in->glist,(gpointer) "Book Name");
    in->glist = g_list_append(in->glist,(gpointer) "Author");
    in->glist = g_list_append(in->glist,(gpointer) "Edition"); 
    in->glist = g_list_append(in->glist,(gpointer) "Type");
    in->glist = g_list_append(in->glist,(gpointer) "Subtype");
    in->glist = g_list_append(in->glist,(gpointer) "Price");
    in->glist = g_list_append(in->glist,(gpointer) "Serial Number");
    gtk_combo_set_popdown_strings(GTK_COMBO(in->combo_box), in->glist) ;
    
    gtk_container_add(GTK_CONTAINER(in->window),in->table);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->entry,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->combo_box,2,3,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->search_button,1,2,3,4);
    gtk_signal_connect(GTK_OBJECT(in->search_button),"clicked",GTK_SIGNAL_FUNC(search_in_bookstore),NULL);   
    gtk_widget_show_all(in->window);

}


/*search in book store */
void search_in_bookstore()
{
    int i,row_initial=0,row_final=1,col_initial=1,col_final=2;
    cnt.count=0;
    int flag=0;


     const gchar *str;
     str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (in->combo_box)->entry));
     if(strcmp(str,"Book Name")==0) {
        ch=1;
	cout<<"found";
	}
     else if(strcmp(str,"Author")==0) {
         ch=2;
	cout<<"found";
	}
      else if(strcmp(str,"Edition")==0) {
         ch=3;
	cout<<"found";
	}
      else if(strcmp(str,"Type")==0) {
         ch=4;
	cout<<"found";
	}
     else if(strcmp(str,"Subtype")==0) {
         ch=5;
	cout<<"found";
	}
     else if(strcmp(str,"Price")==0) {
         ch=6;
	cout<<"found";
	}
     else if(strcmp(str,"Serial Number")==0) {
         ch=7; 
	cout<<"found";
	}
     else {
         ch=0;
	cout<<"not found";
	}

    s=(search_book *)malloc(sizeof(search_book));
    s->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(s->window,400,1000);
    s->table=gtk_table_new(10,7,TRUE);
    gtk_container_add(GTK_CONTAINER(s->window),s->table);
    gtk_table_set_row_spacings(GTK_TABLE(s->table),5);
    gtk_table_set_col_spacings(GTK_TABLE(s->table),10);
    gtk_widget_show(s->table);
    gtk_widget_show(s->window);


    const char* temp=gtk_entry_get_text(GTK_ENTRY(in->entry));
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
                    
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(_delete),gpointer(j));

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
                    
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(_delete),(gpointer)j);

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
                    
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    
                    gtk_widget_show(s->delete_button);
      
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                   
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(_delete),(gpointer)j);

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
                    
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(_delete),(gpointer)j);

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
              
                    s->delete_button=gtk_button_new_with_label("DELETE");
                  
                    gtk_widget_show(s->delete_button);
            
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(_delete),(gpointer)j);

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
                   
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(_delete),(gpointer)j);

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
                    
                    s->delete_button=gtk_button_new_with_label("DELETE");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->delete_button),"clicked",GTK_SIGNAL_FUNC(_delete),(gpointer)j);

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                }        
            }
        }
       
    }
    if(flag==0)
    {
        GtkWidget* b=gtk_button_new_with_label("close");
         GtkWidget* name=gtk_label_new("NO  RESULTS  FOUND!");
         gtk_widget_show(name);
         gtk_widget_show(b);
         gtk_table_attach_defaults(GTK_TABLE(s->table),name,2,5,4,5);
         gtk_table_attach_defaults(GTK_TABLE(s->table),b,5,8,4,5);
         gtk_signal_connect(GTK_OBJECT(b),"clicked",GTK_SIGNAL_FUNC(destroy_delete),NULL);
    }    
}


void _delete(GtkWidget* widget,gpointer row)
{
   int index=(uintptr_t)row;

    cout<<index<<endl;

    data[index].bookName=data[index].author=data[index].edition=data[index].type=data[index].subtype="*****";
    data[index].serialNo=-1;
    data[index].book_price=-1;

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
/*modify book store*/

static void modify_in_bookstore(gchar *string)
{

    in=(insert_new *)malloc(sizeof(insert_new));
    in->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(in->window,400,400);
    gtk_container_set_border_width(GTK_CONTAINER(in->window), 5);
    gtk_window_set_title(GTK_WINDOW(in->window),"MODIFY");
    

    in->table=gtk_table_new(7,3,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(in->table),20);
    gtk_table_set_col_spacings(GTK_TABLE(in->table),20);
    in->entry=gtk_entry_new();
    in->search_button=gtk_button_new_with_label("EDIT");

    in->combo_box=gtk_combo_new();  
    in->glist=NULL;
    in->glist = g_list_append(in->glist,(gpointer) "Book Name");
    in->glist = g_list_append(in->glist,(gpointer) "Author");
    in->glist = g_list_append(in->glist,(gpointer) "Edition"); 
    in->glist = g_list_append(in->glist,(gpointer) "Type");
    in->glist = g_list_append(in->glist,(gpointer) "Subtype");
    in->glist = g_list_append(in->glist,(gpointer) "Price");
    in->glist = g_list_append(in->glist,(gpointer) "Serial Number");
    gtk_combo_set_popdown_strings(GTK_COMBO(in->combo_box), in->glist) ;
    
    gtk_container_add(GTK_CONTAINER(in->window),in->table);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->entry,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->combo_box,2,3,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->search_button,1,2,3,4);
    gtk_signal_connect(GTK_OBJECT(in->search_button),"clicked",GTK_SIGNAL_FUNC(_search_in_bookstore),NULL);   
    gtk_widget_show_all(in->window);

}


/*search in book store */
void _search_in_bookstore()
{
    int i,row_initial=0,row_final=1,col_initial=1,col_final=2;
    cnt.count=0;
    int flag=0;


     const gchar *str;
     str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (in->combo_box)->entry));
     if(strcmp(str,"Book Name")==0) {
        ch=1;
	cout<<"found";
	}
     else if(strcmp(str,"Author")==0) {
         ch=2;
	cout<<"found";
	}
      else if(strcmp(str,"Edition")==0) {
         ch=3;
	cout<<"found";
	}
      else if(strcmp(str,"Type")==0) {
         ch=4;
	cout<<"found";
	}
     else if(strcmp(str,"Subtype")==0) {
         ch=5;
	cout<<"found";
	}
     else if(strcmp(str,"Price")==0) {
         ch=6;
	cout<<"found";
	}
     else if(strcmp(str,"Serial Number")==0) {
         ch=7; 
	cout<<"found";
	}
     else {
         ch=0;
	cout<<"not found";
	}

    s=(search_book *)malloc(sizeof(search_book));
    s->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(s->window,400,1000);
    s->table=gtk_table_new(10,7,TRUE);
    gtk_container_add(GTK_CONTAINER(s->window),s->table);
    gtk_table_set_row_spacings(GTK_TABLE(s->table),5);
    gtk_table_set_col_spacings(GTK_TABLE(s->table),10);
    gtk_widget_show(s->table);
    gtk_widget_show(s->window);


    const char* temp=gtk_entry_get_text(GTK_ENTRY(in->entry));
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
                    
                    gtk_widget_show(s->edit_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);

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
                    
                    gtk_widget_show(s->edit_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);

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
                    
                    gtk_widget_show(s->edit_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);

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
                    
                    gtk_widget_show(s->edit_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);

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
                    
                    gtk_widget_show(s->edit_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);

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
                    
                    gtk_widget_show(s->edit_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);

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
                    
                    gtk_widget_show(s->edit_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->edit_button,2,4,(col_initial),(col_final));
                    
                    gtk_signal_connect(GTK_OBJECT(s->edit_button),"clicked",GTK_SIGNAL_FUNC(edit_in_bookstore),(gpointer)j);

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                }        
            }
        }
       
    }
    if(flag==0)
    {
        GtkWidget* b=gtk_button_new_with_label("close");
         GtkWidget* name=gtk_label_new("NO  RESULTS  FOUND!");
         gtk_widget_show(name);
         gtk_widget_show(b);
         gtk_table_attach_defaults(GTK_TABLE(s->table),name,2,5,4,5);
         gtk_table_attach_defaults(GTK_TABLE(s->table),b,5,8,4,5);
         gtk_signal_connect(GTK_OBJECT(b),"clicked",GTK_SIGNAL_FUNC(destroy_delete),NULL);
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

    e->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);

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
/*search by book name */
static void s1_in_bookstore(gchar *string) {
    in=(insert_new *)malloc(sizeof(insert_new));
    in->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(in->window,400,1000);
    gtk_container_set_border_width(GTK_CONTAINER(in->window), 5);
    gtk_window_set_title(GTK_WINDOW(in->window),"SEARCH");
    

    in->table=gtk_table_new(7,3,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(in->table),20);
    gtk_table_set_col_spacings(GTK_TABLE(in->table),20);
    in->entry=gtk_entry_new();
    in->search_button=gtk_button_new_with_label("SEARCH");

    in->combo_box=gtk_combo_new();  
    in->glist= NULL;
    in->glist = g_list_append(in->glist,(gpointer) "Book Name");
    gtk_combo_set_popdown_strings(GTK_COMBO(in->combo_box), in->glist) ;
    gtk_container_add(GTK_CONTAINER(in->window),in->table);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->entry,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->combo_box,2,3,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->search_button,1,2,3,4);
    gtk_signal_connect(GTK_OBJECT(in->search_button),"clicked",GTK_SIGNAL_FUNC(_search1),NULL);   
    gtk_widget_show_all(in->window);
}
void _search1()
{
    int i,row_initial=0,row_final=1,col_initial=1,col_final=2;
    cnt.count=0;
    int flag=0;


     const gchar *str;
     str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (in->combo_box)->entry));
     if(strcmp(str,"Book Name")==0) {
        ch=1;
	cout<<"found";
	}
	else{ ch=0; cout<<"not found"; }
    s=(search_book *)malloc(sizeof(search_book));
    s->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(s->window,400,400);
    s->table=gtk_table_new(10,7,TRUE);
    gtk_container_add(GTK_CONTAINER(s->window),s->table);
    gtk_table_set_row_spacings(GTK_TABLE(s->table),5);
    gtk_table_set_col_spacings(GTK_TABLE(s->table),10);
    gtk_widget_show(s->table);
    gtk_widget_show(s->window);


    const char* temp=gtk_entry_get_text(GTK_ENTRY(in->entry));
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
                    
                    s->delete_button=gtk_button_new_with_label("FOUND");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                
                }  
            }
        }
if(flag==0)
    {
        GtkWidget* b=gtk_button_new_with_label("close");
         GtkWidget* name=gtk_label_new("NO  RESULTS  FOUND!");
         gtk_widget_show(name);
         gtk_widget_show(b);
         gtk_table_attach_defaults(GTK_TABLE(s->table),name,2,5,4,5);
         gtk_table_attach_defaults(GTK_TABLE(s->table),b,5,8,4,5);
         gtk_signal_connect(GTK_OBJECT(b),"clicked",GTK_SIGNAL_FUNC(destroy_delete),NULL);
    }    
}
}
/*search by author */
static void s2_in_bookstore(gchar *string) {
    in=(insert_new *)malloc(sizeof(insert_new));
    in->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(in->window,400,400);
    gtk_container_set_border_width(GTK_CONTAINER(in->window), 5);
    gtk_window_set_title(GTK_WINDOW(in->window),"SEARCH");
    

    in->table=gtk_table_new(7,3,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(in->table),20);
    gtk_table_set_col_spacings(GTK_TABLE(in->table),20);
    in->entry=gtk_entry_new();
    in->search_button=gtk_button_new_with_label("SEARCH");

    in->combo_box=gtk_combo_new();  
    in->glist= NULL;
    in->glist = g_list_append(in->glist,(gpointer) "Author");
    gtk_combo_set_popdown_strings(GTK_COMBO(in->combo_box), in->glist) ;
    gtk_container_add(GTK_CONTAINER(in->window),in->table);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->entry,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->combo_box,2,3,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->search_button,1,2,3,4);
    gtk_signal_connect(GTK_OBJECT(in->search_button),"clicked",GTK_SIGNAL_FUNC(_search2),NULL);   
    gtk_widget_show_all(in->window);
}
void _search2()
{
    int i,row_initial=0,row_final=1,col_initial=1,col_final=2;
    cnt.count=0;
    int flag=0;


     const gchar *str;
     str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (in->combo_box)->entry));
     if(strcmp(str,"Author")==0) {
        ch=1;
	cout<<"found";
	}
	else{ ch=0; cout<<"not found"; }
    s=(search_book *)malloc(sizeof(search_book));
    s->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(s->window,400,400);
    s->table=gtk_table_new(10,7,TRUE);
    gtk_container_add(GTK_CONTAINER(s->window),s->table);
    gtk_table_set_row_spacings(GTK_TABLE(s->table),5);
    gtk_table_set_col_spacings(GTK_TABLE(s->table),10);
    gtk_widget_show(s->table);
    gtk_widget_show(s->window);


    const char* temp=gtk_entry_get_text(GTK_ENTRY(in->entry));
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
                    
                    s->delete_button=gtk_button_new_with_label("FOUND");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                
                }  
            }
        }
if(flag==0)
    {
        GtkWidget* b=gtk_button_new_with_label("close");
         GtkWidget* name=gtk_label_new("NO  RESULTS  FOUND!");
         gtk_widget_show(name);
         gtk_widget_show(b);
         gtk_table_attach_defaults(GTK_TABLE(s->table),name,2,5,4,5);
         gtk_table_attach_defaults(GTK_TABLE(s->table),b,5,8,4,5);
         gtk_signal_connect(GTK_OBJECT(b),"clicked",GTK_SIGNAL_FUNC(destroy_delete),NULL);
    }    
}
}
/*search by edition */
static void s3_in_bookstore(gchar *string) {
    in=(insert_new *)malloc(sizeof(insert_new));
    in->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(in->window,400,400);
    gtk_container_set_border_width(GTK_CONTAINER(in->window), 5);
    gtk_window_set_title(GTK_WINDOW(in->window),"SEARCH");
    

    in->table=gtk_table_new(7,3,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(in->table),20);
    gtk_table_set_col_spacings(GTK_TABLE(in->table),20);
    in->entry=gtk_entry_new();
    in->search_button=gtk_button_new_with_label("SEARCH");

    in->combo_box=gtk_combo_new();  
    in->glist= NULL;
    in->glist = g_list_append(in->glist,(gpointer) "Edition");
    gtk_combo_set_popdown_strings(GTK_COMBO(in->combo_box), in->glist) ;
    gtk_container_add(GTK_CONTAINER(in->window),in->table);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->entry,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->combo_box,2,3,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->search_button,1,2,3,4);
    gtk_signal_connect(GTK_OBJECT(in->search_button),"clicked",GTK_SIGNAL_FUNC(_search3),NULL);   
    gtk_widget_show_all(in->window);
}
void _search3()
{
    int i,row_initial=0,row_final=1,col_initial=1,col_final=2;
    cnt.count=0;
    int flag=0;


     const gchar *str;
     str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (in->combo_box)->entry));
     if(strcmp(str,"Edition")==0) {
        ch=1;
	cout<<"found";
	}
	else{ ch=0; cout<<"not found"; }
    s=(search_book *)malloc(sizeof(search_book));
    s->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(s->window,400,400);
    s->table=gtk_table_new(10,7,TRUE);
    gtk_container_add(GTK_CONTAINER(s->window),s->table);
    gtk_table_set_row_spacings(GTK_TABLE(s->table),5);
    gtk_table_set_col_spacings(GTK_TABLE(s->table),10);
    gtk_widget_show(s->table);
    gtk_widget_show(s->window);


    const char* temp=gtk_entry_get_text(GTK_ENTRY(in->entry));
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
                    
                    s->delete_button=gtk_button_new_with_label("FOUND");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                
                }  
            }
        }
if(flag==0)
    {
        GtkWidget* b=gtk_button_new_with_label("close");
         GtkWidget* name=gtk_label_new("NO  RESULTS  FOUND!");
         gtk_widget_show(name);
         gtk_widget_show(b);
         gtk_table_attach_defaults(GTK_TABLE(s->table),name,2,5,4,5);
         gtk_table_attach_defaults(GTK_TABLE(s->table),b,5,8,4,5);
         gtk_signal_connect(GTK_OBJECT(b),"clicked",GTK_SIGNAL_FUNC(destroy_delete),NULL);
    }    
}
}
/*search by type */
static void s4_in_bookstore(gchar *string) {
    in=(insert_new *)malloc(sizeof(insert_new));
    in->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(in->window,400,400);
    gtk_container_set_border_width(GTK_CONTAINER(in->window), 5);
    gtk_window_set_title(GTK_WINDOW(in->window),"SEARCH");
    

    in->table=gtk_table_new(7,3,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(in->table),20);
    gtk_table_set_col_spacings(GTK_TABLE(in->table),20);
    in->entry=gtk_entry_new();
    in->search_button=gtk_button_new_with_label("SEARCH");

    in->combo_box=gtk_combo_new();  
    in->glist= NULL;
    in->glist = g_list_append(in->glist,(gpointer) "Type");
    gtk_combo_set_popdown_strings(GTK_COMBO(in->combo_box), in->glist) ;
    gtk_container_add(GTK_CONTAINER(in->window),in->table);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->entry,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->combo_box,2,3,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->search_button,1,2,3,4);
    gtk_signal_connect(GTK_OBJECT(in->search_button),"clicked",GTK_SIGNAL_FUNC(_search4),NULL);   
    gtk_widget_show_all(in->window);
}
void _search4()
{
    int i,row_initial=0,row_final=1,col_initial=1,col_final=2;
    cnt.count=0;
    int flag=0;


     const gchar *str;
     str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (in->combo_box)->entry));
     if(strcmp(str,"Type")==0) {
        ch=1;
	cout<<"found";
	}
	else{ ch=0; cout<<"not found"; }
    s=(search_book *)malloc(sizeof(search_book));
    s->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(s->window,400,400);
    s->table=gtk_table_new(10,7,TRUE);
    gtk_container_add(GTK_CONTAINER(s->window),s->table);
    gtk_table_set_row_spacings(GTK_TABLE(s->table),5);
    gtk_table_set_col_spacings(GTK_TABLE(s->table),10);
    gtk_widget_show(s->table);
    gtk_widget_show(s->window);


    const char* temp=gtk_entry_get_text(GTK_ENTRY(in->entry));
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
                    
                    s->delete_button=gtk_button_new_with_label("FOUND");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                
                }  
            }
        }
if(flag==0)
    {
        GtkWidget* b=gtk_button_new_with_label("close");
         GtkWidget* name=gtk_label_new("NO  RESULTS  FOUND!");
         gtk_widget_show(name);
         gtk_widget_show(b);
         gtk_table_attach_defaults(GTK_TABLE(s->table),name,2,5,4,5);
         gtk_table_attach_defaults(GTK_TABLE(s->table),b,5,8,4,5);
         gtk_signal_connect(GTK_OBJECT(b),"clicked",GTK_SIGNAL_FUNC(destroy_delete),NULL);
    }    
}
}
/*search by type */
static void s5_in_bookstore(gchar *string) {
    in=(insert_new *)malloc(sizeof(insert_new));
    in->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(in->window,400,400);
    gtk_container_set_border_width(GTK_CONTAINER(in->window), 5);
    gtk_window_set_title(GTK_WINDOW(in->window),"SEARCH");
    

    in->table=gtk_table_new(7,3,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(in->table),20);
    gtk_table_set_col_spacings(GTK_TABLE(in->table),20);
    in->entry=gtk_entry_new();
    in->search_button=gtk_button_new_with_label("SEARCH");

    in->combo_box=gtk_combo_new();  
    in->glist= NULL;
    in->glist = g_list_append(in->glist,(gpointer) "SubType");
    gtk_combo_set_popdown_strings(GTK_COMBO(in->combo_box), in->glist) ;
    gtk_container_add(GTK_CONTAINER(in->window),in->table);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->entry,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->combo_box,2,3,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->search_button,1,2,3,4);
    gtk_signal_connect(GTK_OBJECT(in->search_button),"clicked",GTK_SIGNAL_FUNC(_search5),NULL);   
    gtk_widget_show_all(in->window);
}
void _search5()
{
    int i,row_initial=0,row_final=1,col_initial=1,col_final=2;
    cnt.count=0;
    int flag=0;


     const gchar *str;
     str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (in->combo_box)->entry));
     if(strcmp(str,"Subtype")==0) {
        ch=1;
	cout<<"found";
	}
	else{ ch=0; cout<<"not found"; }
    s=(search_book *)malloc(sizeof(search_book));
    s->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(s->window,400,400);
    s->table=gtk_table_new(10,7,TRUE);
    gtk_container_add(GTK_CONTAINER(s->window),s->table);
    gtk_table_set_row_spacings(GTK_TABLE(s->table),5);
    gtk_table_set_col_spacings(GTK_TABLE(s->table),10);
    gtk_widget_show(s->table);
    gtk_widget_show(s->window);


    const char* temp=gtk_entry_get_text(GTK_ENTRY(in->entry));
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
                    
                    s->delete_button=gtk_button_new_with_label("FOUND");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                
                }  
            }
        }
if(flag==0)
    {
        GtkWidget* b=gtk_button_new_with_label("close");
         GtkWidget* name=gtk_label_new("NO  RESULTS  FOUND!");
         gtk_widget_show(name);
         gtk_widget_show(b);
         gtk_table_attach_defaults(GTK_TABLE(s->table),name,2,5,4,5);
         gtk_table_attach_defaults(GTK_TABLE(s->table),b,5,8,4,5);
         gtk_signal_connect(GTK_OBJECT(b),"clicked",GTK_SIGNAL_FUNC(destroy_delete),NULL);
    }    
}
}
/*search by price */
static void s6_in_bookstore(gchar *string) {
    in=(insert_new *)malloc(sizeof(insert_new));
    in->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(in->window,400,1000);
    gtk_container_set_border_width(GTK_CONTAINER(in->window), 5);
    gtk_window_set_title(GTK_WINDOW(in->window),"SEARCH");
    

    in->table=gtk_table_new(7,3,TRUE);
    gtk_table_set_row_spacings(GTK_TABLE(in->table),20);
    gtk_table_set_col_spacings(GTK_TABLE(in->table),20);
    in->entry=gtk_entry_new();
    in->search_button=gtk_button_new_with_label("SEARCH");

    in->combo_box=gtk_combo_new();  
    in->glist= NULL;
    in->glist = g_list_append(in->glist,(gpointer) "Price");
    gtk_combo_set_popdown_strings(GTK_COMBO(in->combo_box), in->glist) ;
    gtk_container_add(GTK_CONTAINER(in->window),in->table);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->entry,1,2,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->combo_box,2,3,2,3);
    gtk_table_attach_defaults(GTK_TABLE(in->table),in->search_button,1,2,3,4);
    gtk_signal_connect(GTK_OBJECT(in->search_button),"clicked",GTK_SIGNAL_FUNC(_search6),NULL);   
    gtk_widget_show_all(in->window);
}
void _search6()
{
    int i,row_initial=0,row_final=1,col_initial=1,col_final=2;
    cnt.count=0;
    int flag=0;


     const gchar *str;
     str = gtk_entry_get_text (GTK_ENTRY (GTK_COMBO (in->combo_box)->entry));
     if(strcmp(str,"Price")==0) {
        ch=1;
	cout<<"found";
	}
	else{ ch=0; cout<<"not found"; }
    s=(search_book *)malloc(sizeof(search_book));
    s->window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(s->window,400,400);
    s->table=gtk_table_new(10,7,TRUE);
    gtk_container_add(GTK_CONTAINER(s->window),s->table);
    gtk_table_set_row_spacings(GTK_TABLE(s->table),5);
    gtk_table_set_col_spacings(GTK_TABLE(s->table),10);
    gtk_widget_show(s->table);
    gtk_widget_show(s->window);


    const char* temp=gtk_entry_get_text(GTK_ENTRY(in->entry));
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
                    temp_book_details=data[j].bookName+"\n\n"+data[j].author+"\n\n"+data[j].edition+"\n\n"+data[j].type+"\n\n"+data[j].subtype+"\n\n"+data[j].book_price+"\n\n"+data[j].serialNo; 
                     std::transform(temp_book_details.begin(), temp_book_details.end(), temp_book_details.begin(), ::toupper);
                    const char* temp_label=temp_book_details.c_str();

                    s->frame=gtk_frame_new("");
                    s->label=gtk_label_new(temp_label);
                    gtk_container_add(GTK_CONTAINER(s->frame),s->label);
                    gtk_widget_show(s->label);
                    
                    s->delete_button=gtk_button_new_with_label("FOUND");
                    
                    gtk_widget_show(s->delete_button);
                    
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->delete_button,4,6,(col_initial),(col_final));
                    
                    

                    gtk_widget_show(s->frame);
                    gtk_table_attach_defaults(GTK_TABLE(s->table),s->frame,0,2,(col_initial-1),(col_final)+2);
                    col_initial+=4;col_final+=4;
                
                }  
            }
        }
if(flag==0)
    {
        GtkWidget* b=gtk_button_new_with_label("close");
         GtkWidget* name=gtk_label_new("NO  RESULTS  FOUND!");
         gtk_widget_show(name);
         gtk_widget_show(b);
         gtk_table_attach_defaults(GTK_TABLE(s->table),name,2,5,4,5);
         gtk_table_attach_defaults(GTK_TABLE(s->table),b,5,8,4,5);
         gtk_signal_connect(GTK_OBJECT(b),"clicked",GTK_SIGNAL_FUNC(destroy_delete),NULL);
    }    
}
}


