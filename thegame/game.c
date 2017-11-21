#include<gtk/gtk.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#define left 20
#define right 40
#define top 0
#define bottom 20
#define side 20
typedef struct arrowtype
{
    int row;
    int col;
    char disp[];//={">>-->"};
}arrowtype;
typedef struct balltype
{
    int row;
    int col;
    char disp[];
}balltype;
int terminate_now=0,hits=0,rounds=0,loseindex=-1,winindex=-1,lifes_left=3,ball_speed=300;
GtkWidget *create_arrow_button( GtkArrowType  arrow_type,GtkShadowType shadow_type );
void attach_to_table(GtkWidget *playbutton,GtkWidget *shootbutton,GtkWidget *bb1,GtkWidget *bb2,GtkWidget *bb3);
gboolean arrow_move(gpointer data);
void shoot_clicked(GtkWidget *button,gpointer data);
gboolean you_lose_display(gpointer data);
void call_on_lose();
void call_on_win();
void chose_mode(GtkWidget *widget,gpointer data);
GtkWidget *imagebaloon,*imageleft1,*imageleft2,*imageleft3,*labels[side][side],*resultlabel;
GtkWidget *loseimage,*shotimage,*table,*scorecard;
arrowtype *arrow;
balltype *ball;
char temp[30];
int default_row=10;
void refresh()
{
    int i,j,k;
    terminate_now=0; hits=0; rounds=0;
    loseindex=-1;winindex=-1; lifes_left=3;
    /*arrow->row=10;*/arrow->row=default_row;arrow->col=0;
    ball->col=3;ball->row=1;

    for(k=0;k<side*side;k++)
    {
        i=k%side;j=k/side;
        if(i==0 || j==0 || i==side-1 || j==side-1)
            gtk_label_set(GTK_LABEL(labels[i][j]),"~~~~~\n~~~~~");
        else
        gtk_label_set(GTK_LABEL(labels[i][j]),"     \n     ");
    }

    gtk_label_set(GTK_LABEL(labels[arrow->col][arrow->row]),arrow->disp);//initial arrow pos
    gtk_image_set_from_file(GTK_IMAGE(loseimage),"s_think.jpg");
    sprintf(temp,"Balls left:%.0f  Arrows left:%.0f\n       Score:%.0f",(float)(4-rounds),(float)lifes_left,(float)hits);
    gtk_label_set(GTK_LABEL(scorecard),temp);
}
int main(int argc,char *argv[])
{
    int i=0,j=0,k=0;
    gtk_init(&argc,&argv);
    GtkWidget *window,*playbutton,*shootbutton,*bb1,*bb2,*bb3;
    GdkColor color;
    gdk_color_parse("red",&color);
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window,400,400);
    gtk_window_set_title(GTK_WINDOW(window),"BALLON N ARROW GAME");
    gtk_widget_modify_bg(GTK_WIDGET(window),GTK_STATE_NORMAL,&color);
    g_signal_connect(G_OBJECT(window),"delete-event",gtk_main_quit,NULL);
    arrow=(arrowtype *)malloc(sizeof(arrowtype));
    /*arrow->row=10;*/arrow->row=default_row;arrow->col=0;strcpy(arrow->disp,">>-->\n     ");
    ball=(balltype *)malloc(sizeof(balltype));
    ball->col=3;ball->row=1;strcpy(ball->disp,"/~~~\\\n\\____/");
    table=gtk_table_new(side+1,20+side+20,0);
    attach_to_table(playbutton,shootbutton,bb1,bb2,bb3);
    gtk_container_add(GTK_CONTAINER(window),table);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
void up_arrow_clicked(GtkWidget *widget,gpointer data)
{
    int temprow=arrow->row;
    g_print("1\n");
    if(arrow->row==1)
        return;
    arrow->row=temprow-1;
    default_row=arrow->row;
    gtk_label_set(GTK_LABEL(labels[arrow->col][temprow]),"~~~~~\n~~~~~");
    gtk_label_set(GTK_LABEL(labels[arrow->col][arrow->row]),arrow->disp);
}
void down_arrow_clicked(GtkWidget *widget,gpointer data)
{
    int temprow=arrow->row;
    g_print("2\n");
    if(arrow->row==18)
        return;
    arrow->row=temprow+1;
    default_row=arrow->row;
    gtk_label_set(GTK_LABEL(labels[arrow->col][temprow]),"~~~~~\n~~~~~");
    gtk_label_set(GTK_LABEL(labels[arrow->col][arrow->row]),arrow->disp);
}
void final_results()
{
    if(lifes_left==0 || rounds==4)
    {
        if(hits>=2)
            call_on_win();
        else
            call_on_lose();
    }
}

gboolean ball_fall(gpointer data)
{

    int temprow=ball->row;
    if(terminate_now==1)
        return FALSE;
    gtk_label_set(GTK_LABEL(labels[ball->col][temprow]),ball->disp);
    if((ball->row==arrow->row) && (ball->col==arrow->col))
    {
        hits++;
        rounds++;
        ball->row=1;
        ball->col=ball->col+1;
        /*arrow->row=10;*/arrow->row=default_row;
        arrow->col=0;
        gtk_label_set(GTK_LABEL(labels[arrow->col][arrow->row]),arrow->disp);
        sprintf(temp,"Balls left:%.0f  Arrows left:%.0f\n       Score:%.0f",(float)(4-rounds),(float)lifes_left,(float)hits);
        gtk_label_set(GTK_LABEL(scorecard),temp);
        return TRUE;
    }
    if(ball->row==18)
    {
        rounds++;
        sprintf(temp,"Balls left:%.0f  Arrows left:%.0f\n       Score:%.0f",(float)(4-rounds),(float)lifes_left,(float)hits);
        gtk_label_set(GTK_LABEL(scorecard),temp);
        if(rounds==4)//4 balls
        {
            final_results();
            return FALSE;
        }
        if(lifes_left<=0)
        {
            terminate_now=1;
            final_results();
            return FALSE;
        }

        ball->row=1;
        ball->col=ball->col+1;
        return TRUE;
    }

    ball->row=temprow+1;
    gtk_label_set(GTK_LABEL(labels[ball->col][temprow]),"     \n     ");
    gtk_label_set(GTK_LABEL(labels[ball->col][ball->row]),ball->disp);
    return TRUE;
}

void play_clicked(GtkWidget *button,gpointer data)
{
    refresh();
    g_timeout_add(ball_speed,ball_fall,NULL);
}
gboolean arrow_move(gpointer data)
{
    //char temp[30];
    int tempcol=arrow->col;
    gtk_label_set(GTK_LABEL(labels[tempcol][arrow->row]),arrow->disp);
    if(((arrow->row==ball->row)||(arrow->row==(ball->row+1))) && (arrow->col==ball->col))
    {
        rounds++;
        hits++;
        sprintf(temp,"Balls left:%.0f  Arrows left:%.0f\n       Score:%.0f",(float)(4-rounds),(float)lifes_left,(float)hits);
        gtk_label_set(GTK_LABEL(scorecard),temp);
        /*arrow->row=10;*/arrow->row=default_row;
        arrow->col=0;
        gtk_label_set(GTK_LABEL(labels[arrow->col][arrow->row]),arrow->disp);
        ball->row=1;
        ball->col=ball->col+1;
        if(lifes_left==0 || rounds==4)
        {
            terminate_now=1;
            final_results();
        }
        else
        {
            /*arrow->row=10;*/arrow->row=default_row;
            arrow->col=0;
            gtk_label_set(GTK_LABEL(labels[arrow->col][arrow->row]),arrow->disp);
        }
        return FALSE;
    }
    if(arrow->col==18)
    {
        lifes_left--;
        /*arrow->row=10;*/arrow->row=default_row;arrow->col=0;
        gtk_label_set(GTK_LABEL(labels[arrow->col][arrow->row]),arrow->disp);
        sprintf(temp,"Balls left:%.0f  Arrows left:%.0f\n       Score:%.0f",(float)(4-rounds),(float)lifes_left,(float)hits);
        gtk_label_set(GTK_LABEL(scorecard),temp);
        if(lifes_left==0)
        {
            terminate_now=1;
            final_results();
        }
        return FALSE;
    }
    arrow->col=tempcol+1;
    gtk_label_set(GTK_LABEL(labels[tempcol][arrow->row]),"     \n     ");
    gtk_label_set(GTK_LABEL(labels[arrow->col][arrow->row]),arrow->disp);

    return TRUE;

}

void shoot_clicked(GtkWidget *button,gpointer data)
{
    g_timeout_add(100,arrow_move,NULL);
}
/*gboolean wrapper(GtkWidget *widget,GdkEventKey *event,gpointer data)//shoot by space
{
    if(event->keyval==' ')
    {
        lifes_left--;
        g_timeout_add(100,arrow_move,NULL);
    }
    return FALSE;
}*/
void attach_to_table(GtkWidget *playbutton,GtkWidget *shootbutton,GtkWidget *bb1,GtkWidget *bb2,GtkWidget *bb3)
{
    GtkWidget *msglabel,*up,*down;
    int i=0,j=0,k=0;
    playbutton=gtk_button_new_with_mnemonic("Play");
    gtk_table_attach_defaults(GTK_TABLE(table),playbutton,side+20,side+35,15,16);
    g_signal_connect(G_OBJECT(playbutton),"clicked",play_clicked,NULL);
    shootbutton=gtk_button_new_with_mnemonic("SHOOT");
    gtk_table_attach_defaults(GTK_TABLE(table),shootbutton,side+20,side+35,14,15);
    g_signal_connect(G_OBJECT(shootbutton),"clicked",shoot_clicked,NULL);
    g_signal_connect(G_OBJECT(shootbutton),"key_press_event",shoot_clicked,NULL);
up=create_arrow_button (GTK_ARROW_UP, GTK_SHADOW_IN);
gtk_table_attach_defaults(GTK_TABLE(table),up,side+35,side+40,14,15);
g_signal_connect(G_OBJECT(up),"clicked",up_arrow_clicked,NULL);
down=create_arrow_button (GTK_ARROW_DOWN, GTK_SHADOW_OUT);
gtk_table_attach_defaults(GTK_TABLE(table),down,side+35,side+40,15,16);
g_signal_connect(G_OBJECT(down),"clicked",down_arrow_clicked,NULL);
    imageleft1=gtk_image_new_from_file("s_action.jpg");
    gtk_table_attach_defaults(GTK_TABLE(table),imageleft1,0,20,0,6);
    imageleft2=gtk_image_new_from_file("shero.jpg");
    gtk_table_attach_defaults(GTK_TABLE(table),imageleft2,0,10,6,14);
    imageleft3=gtk_image_new_from_file("s_action.jpg");
    gtk_table_attach_defaults(GTK_TABLE(table),imageleft3,0,10,14,20);
    shotimage=gtk_image_new_from_file("shot1.jpg");
    gtk_table_attach_defaults(GTK_TABLE(table),shotimage,side+20,side+40,0,6);
    loseimage=gtk_image_new_from_file("s_think.jpg");
    gtk_table_attach_defaults(GTK_TABLE(table),loseimage,side+20,side+40,6,14);
    bb1=gtk_button_new_with_mnemonic("EASY");
    gtk_table_attach_defaults(GTK_TABLE(table),bb1,side+20,side+26,16,17);
    bb2=gtk_button_new_with_mnemonic("MED");
    gtk_table_attach_defaults(GTK_TABLE(table),bb2,side+26,side+34,16,17);
    bb3=gtk_button_new_with_mnemonic("HARD");
    gtk_table_attach_defaults(GTK_TABLE(table),bb3,side+34,side+40,16,17);
    g_signal_connect(G_OBJECT(bb1),"clicked",chose_mode,NULL);
    g_signal_connect(G_OBJECT(bb2),"clicked",chose_mode,NULL);
    g_signal_connect(G_OBJECT(bb3),"clicked",chose_mode,NULL);
    msglabel=gtk_label_new("You have got total 4 balls!!\nMaximum 3 arrowscan be wasted\nScore at least 2...\nAnd Shin Chan will dance for u.. :)");
    gtk_table_attach_defaults(GTK_TABLE(table),msglabel,side+20,side+40,17,18);
    scorecard=gtk_label_new("Balls left:4  Arrows left:3\n       Score:0");
    gtk_table_attach_defaults(GTK_TABLE(table),scorecard,side+20,side+40,18,19);
    for(k=0;k<side*side;k++)
    {
        i=k%side;j=k/side;
        if(i==0 || j==0 || i==side-1 || j==side-1)
            labels[i][j]=gtk_label_new("~~~~~\n~~~~~");
        else
        labels[i][j]=gtk_label_new("     \n     ");
        gtk_table_attach_defaults(GTK_TABLE(table),labels[i][j],i+left,i+1+left,j,j+1);
    }
    gtk_label_set(GTK_LABEL(labels[arrow->col][arrow->row]),arrow->disp);//initial arrow pos
}

gboolean you_win_display(gpointer data)
{
    if(winindex==0)
        gtk_image_set_from_file(GTK_IMAGE(loseimage),"win1(1).jpg");
    else
    if(winindex==1)
        gtk_image_set_from_file(GTK_IMAGE(loseimage),"win2(2).jpg");
    winindex=1-winindex;
    return TRUE;
}
void call_on_win()
{
    winindex=0;
    g_timeout_add(500,you_win_display,NULL);
}

gboolean you_lose_display(gpointer data)
{
    if(loseindex==0)
        gtk_image_set_from_file(GTK_IMAGE(loseimage),"try_again1.jpg");
    else
    if(loseindex==1)
        gtk_image_set_from_file(GTK_IMAGE(loseimage),"you_lose1.jpg");
    loseindex=1-loseindex;
    return TRUE;
}
void call_on_lose()
{
    loseindex=0;
    g_timeout_add(500,you_lose_display,NULL);
}
void chose_mode(GtkWidget *widget,gpointer data)
{
    char *modelabel=gtk_button_get_label(GTK_LABEL(widget));
    if(strcmp(modelabel,"EASY")==0)
        ball_speed=500;
    else
        if(strcmp(modelabel,"MED")==0)
            ball_speed=300;
    else
        if(strcmp(modelabel,"HARD")==0)
            ball_speed=200;
}
GtkWidget *create_arrow_button( GtkArrowType  arrow_type,GtkShadowType shadow_type )
{
  GtkWidget *button;
  GtkWidget *arrow;

  button = gtk_button_new ();
  arrow = gtk_arrow_new (arrow_type, shadow_type);

  gtk_container_add (GTK_CONTAINER (button), arrow);

  gtk_widget_show (button);
  gtk_widget_show (arrow);

  return button;
}
