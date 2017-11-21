#include<gtk/gtk.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int stop_button_clicked = 0;
int pause_clicked = 0;
int int_frac = 0; int f=0,n=0;
char temp[20];

GtkObject *adj1; // adjustment object not a widget
GtkWidget *combo;
typedef struct _progress_bar
{
    GtkWidget* pbar;
    GtkWidget* scale;
    GtkWidget* label;
    GtkWidget *button_play_pause;
    int timer;
    int time_elapsed;
    gboolean activity_mode;
}ProgressBar;

ProgressBar *p;

void set_orientation_right()
{
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(p->pbar), GTK_PROGRESS_LEFT_TO_RIGHT);
}   
void set_orientation_left()
{
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(p->pbar), GTK_PROGRESS_RIGHT_TO_LEFT);
}   

void set(GtkWidget *widget,gpointer  data) {
if(strcmp(data,"Right to Left")==0) {
f=1;
set_orientation_right();
}
else {
f=0;
set_orientation_left();
}
}


GtkWidget *CreateCombobox ()
{
GList *cbitems = NULL;
GtkWidget *combo;
cbitems = g_list_append (cbitems, "Left to Right");
cbitems = g_list_append (cbitems, "Right to Left");
combo = gtk_combo_new ();
gtk_combo_set_popdown_strings (GTK_COMBO(combo), cbitems);
gtk_entry_set_text (GTK_ENTRY (GTK_COMBO(combo)->entry),"Left to Right");
//gtk_entry_set_editable (GTK_ENTRY (GTK_COMBO (combo)->entry), FALSE);
gchar *my_data;
my_data=gtk_entry_get_text(GTK_ENTRY(GTK_COMBO (combo)->entry));
g_signal_connect(G_OBJECT(GTK_COMBO(combo)->entry), "activate",G_CALLBACK (set), (gpointer) my_data);
return (combo); 
}


int update_timer(GtkWidget *widget)
{
    double fraction=0.0;

    if((p->timer)>0)
    {
        p->time_elapsed+=1;
        fraction=((double)(p->time_elapsed)/(double)((p->timer)*10));
        int_frac=fraction;
        float percentage = fraction * 100;
        sprintf(temp,"%3.2f",percentage);
        strcat(temp,"%");
	strcat(temp," completed");
        if(fraction <= 1 && stop_button_clicked!=1)
        {
            gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(p->pbar),fraction);
            gtk_progress_bar_set_text(GTK_PROGRESS_BAR(p->pbar),temp);
        }
    }

        if(fraction>1 || stop_button_clicked==1 || pause_clicked==1)
        {
            if(int_frac == 1)
            {
                gtk_button_set_label(GTK_BUTTON(p->button_play_pause),"PLAY");
            }
            gtk_timeout_remove(FALSE);
        }
        else
            return TRUE;
}

void change_count(GtkAdjustment * adj)   /* which changes the count */
{
    char* str;
    str=malloc(100*sizeof(char));
    sprintf(str,"%.2f",adj->value);
    gtk_label_set_text(GTK_LABEL(p->label),str);
    if(p->activity_mode==0)
    {
        p->timer=adj->value;
        p->timer++;
    }
}

void play_pause_clicked(GtkWidget *widget,GtkAdjustment *adj)
{

    if((adj->value)>0)
    {

        p->activity_mode=1;
        const char* text=gtk_button_get_label(GTK_BUTTON(widget));
        if(strcmp(text,"PLAY")==0)
        {
            stop_button_clicked=0;
            pause_clicked=0;
            gtk_button_set_label(GTK_BUTTON(widget),"PAUSE");
            gtk_timeout_add(100,(GtkFunction)update_timer, p);
        }
        else
        {
            pause_clicked=1;
            stop_button_clicked=1;
            gtk_button_set_label(GTK_BUTTON(widget),"PLAY");
        }
    }
    return;
}

void stop_clicked(GtkWidget *window)
{
    p->timer = 0;
    p->time_elapsed = 0;
    stop_button_clicked = 1;
    p->activity_mode = 0;

    gtk_button_set_label(GTK_BUTTON(p->button_play_pause),"PLAY");
    gtk_label_set_text(GTK_LABEL(p->label),"0");
    gtk_adjustment_set_value( GTK_ADJUSTMENT(adj1),0);
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(p->pbar),"");
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(p->pbar),(double)0);
}


int main(int argc, char** argv)
{
    gtk_init(&argc,&argv);

    p=malloc(sizeof(ProgressBar));

    p->timer=0;
    p->time_elapsed=0;
    p->activity_mode=0;

    GtkWidget* window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window,400,400);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
    gtk_window_set_title(GTK_WINDOW(window),"Progress Bar");

    /* frame and label */
    GtkWidget *frame,*table,*hbox;

    frame=gtk_frame_new("Scale Value");
    hbox=gtk_hbox_new(TRUE,1);
    gtk_widget_set_size_request(frame,1,1);
    p->label=gtk_label_new("0");
    gtk_container_add(GTK_CONTAINER(frame),p->label);

     /*table*/
    table=gtk_table_new(4,4,TRUE);
    gtk_table_set_col_spacing(GTK_TABLE(table),1,10);
    gtk_table_set_col_spacing(GTK_TABLE(table),0,10);
    gtk_table_attach_defaults(GTK_TABLE(table),frame,2,4,2,3);
    gtk_container_add(GTK_CONTAINER(window),table);

    combo=CreateCombobox();
    /* scale and adjustnt */


    adj1=gtk_adjustment_new(0, 0, 101, 1, 10, 1);  // setting the values,lower,upper,step_increment,page_increment,pagesize

    p->scale=gtk_hscale_new(GTK_ADJUSTMENT(adj1));   // gtk_hscale_new(): takes the argument of GtkObject*
    gtk_scale_set_draw_value( GTK_SCALE(p->scale),FALSE);
    gtk_widget_set_can_focus(GTK_WIDGET(p->scale),FALSE); // to remove the dotted line around a widget
    gtk_widget_set_size_request(GTK_WIDGET(p->scale),20,20);

    gtk_signal_connect(GTK_OBJECT(adj1),"value_changed",GTK_SIGNAL_FUNC(change_count),&p); // "value_changed"  is the event
    gtk_table_attach_defaults(GTK_TABLE(table),hbox,0,4,1,2);
    gtk_box_pack_start(GTK_BOX(hbox),p->scale,TRUE,TRUE,1);

    p->pbar=gtk_progress_bar_new();
    gtk_table_attach_defaults(GTK_TABLE(table),p->pbar,0,4,0,1);

    p->button_play_pause=gtk_button_new_with_label("PLAY");
    GdkColor color1;
    gdk_color_parse ("green", &color1);
    gtk_widget_modify_bg(GTK_WIDGET(p->button_play_pause), GTK_STATE_NORMAL, &color1);
    GtkWidget* stop=gtk_button_new_with_label("RESET");
    GdkColor color2;
    gdk_color_parse ("red", &color2);
    gtk_widget_modify_bg(GTK_WIDGET(stop), GTK_STATE_NORMAL, &color2);
    gtk_widget_set_size_request(GTK_WIDGET(p->button_play_pause),2,5);
    gtk_widget_set_size_request(GTK_WIDGET(stop),5,5);
    gtk_table_attach_defaults(GTK_TABLE(table),p->button_play_pause,0,1,2,3);
    gtk_table_attach_defaults(GTK_TABLE(table),stop,1,2,2,3);

    gtk_signal_connect(GTK_OBJECT(p->button_play_pause),"clicked",GTK_SIGNAL_FUNC(play_pause_clicked),adj1);
    gtk_signal_connect(GTK_OBJECT(stop),"clicked",GTK_SIGNAL_FUNC(stop_clicked),&p);


    /*GtkWidget *b1,*b2;
    b1=gtk_button_new_with_label("LEFT");
    b2=gtk_button_new_with_label("RIGHT");
    gtk_table_attach_defaults(GTK_TABLE(table),b1,0,1,3,4);
    gtk_table_attach_defaults(GTK_TABLE(table),b2,1,2,3,4);
    gtk_signal_connect(GTK_OBJECT(b1),"clicked",GTK_SIGNAL_FUNC(set_orientation_left),NULL);
    gtk_signal_connect(GTK_OBJECT(b2),"clicked",GTK_SIGNAL_FUNC(set_orientation_right),NULL);
*/
    gtk_table_attach_defaults(GTK_TABLE(table),combo,0,2,3,4);

    GtkWidget *button = gtk_button_new_with_label ("Q U I T");
    gtk_table_attach_defaults(GTK_TABLE(table),button,2,4,3,4);
        g_signal_connect_swapped (G_OBJECT (button), "clicked",
                              G_CALLBACK (gtk_main_quit),
                              G_OBJECT (window));

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
