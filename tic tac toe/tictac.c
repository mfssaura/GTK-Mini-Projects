#include<gtk/gtk.h>
#include<string.h>
int turn=0;
GtkWidget *mark[3][3];
GtkWidget *turn_info;
void reset(GtkWidget *reset,GtkWidget *window)
{
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			gtk_label_set(GTK_LABEL(mark[i][j]),"");
		}
	}
	gtk_widget_destroy(window);
}
void out(GtkWidget *quit,GtkWidget *window)
{
	gtk_widget_destroy(window);
	gtk_main_quit();
}
void destroy(GtkWidget *button,GtkWidget *window)
{
	gtk_widget_destroy(window);
}
void check()
{
	int i,j,count=0;
	char m[3][3];
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			char *tmp=(char *)gtk_label_get_label(GTK_LABEL(mark[i][j]));
			m[i][j]=tmp[0];
			if(strlen(tmp)>0)
			{
				count++;
			}
		}
	}
	if(((m[0][0]=='X'&&m[0][1]=='X'&&m[0][2]=='X')||(m[0][0]=='X'&&m[1][0]=='X'&&m[2][0]=='X')||(m[0][0]=='X'&&m[1][1]=='X'&&m[2][2]=='X')||(m[1][0]=='X'&&m[1][1]=='X'&&m[1][2]=='X')||(m[2][0]=='X'&&m[2][1]=='X'&&m[2][2]=='X')||(m[0][1]=='X'&&m[1][1]=='X'&&m[2][1]=='X')||(m[0][2]=='X'&&m[1][2]=='X'&&m[2][2]=='X')||(m[2][0]=='X'&&m[1][1]=='X'&&m[0][2]=='X'))||((m[0][0]=='0'&&m[0][1]=='0'&&m[0][2]=='0')||(m[0][0]=='0'&&m[1][0]=='0'&&m[2][0]=='0')||(m[0][0]=='0'&&m[1][1]=='0'&&m[2][2]=='0')||(m[1][0]=='0'&&m[1][1]=='0'&&m[1][2]=='0')||(m[2][0]=='0'&&m[2][1]=='0'&&m[2][2]=='0')||(m[0][1]=='0'&&m[1][1]=='0'&&m[2][1]=='0')||(m[0][2]=='0'&&m[1][2]=='0'&&m[2][2]=='0')||(m[2][0]=='0'&&m[1][1]=='0'&&m[0][2]=='0')))
	{
		GtkWidget *message;
		GtkWidget *replay,*quit;
		GtkWidget *label;
		GtkWidget *vbox,*hbox;
		GtkWidget *frame;
		char string[25];
		sprintf(string,"Player %d won the puzzle",2-turn);
		message=gtk_window_new(GTK_WINDOW_POPUP);
		gtk_window_set_position(GTK_WINDOW(message),GTK_WIN_POS_CENTER);
		gtk_window_resize(GTK_WINDOW(message),200,100);
		gtk_window_set_modal(GTK_WINDOW(message),TRUE);
		frame=gtk_frame_new(NULL);
		replay=gtk_button_new_with_label("Play Again");
		quit=gtk_button_new_with_label("Exit");
		label=gtk_label_new(string);
		vbox=gtk_vbox_new(0,0);
		hbox=gtk_hbox_new(1,0);
		gtk_container_add(GTK_CONTAINER(message),frame);
		gtk_container_add(GTK_CONTAINER(frame),vbox);
		gtk_box_pack_start(GTK_BOX(vbox),label,0,0,0);
		gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
		gtk_box_pack_start(GTK_BOX(hbox),replay,1,1,0);
		gtk_box_pack_start(GTK_BOX(hbox),quit,1,1,0);
		g_signal_connect(GTK_OBJECT(replay),"clicked",GTK_SIGNAL_FUNC(reset),message);
		g_signal_connect(GTK_OBJECT(quit),"clicked",GTK_SIGNAL_FUNC(out),message);
		gtk_widget_show_all(message);
	}
	else if(count==9)
	{
		GtkWidget *message;
		GtkWidget *replay,*quit;
		GtkWidget *label;
		GtkWidget *vbox,*hbox;
		GtkWidget *frame;
		message=gtk_window_new(GTK_WINDOW_POPUP);
		gtk_window_set_position(GTK_WINDOW(message),GTK_WIN_POS_CENTER);
		gtk_window_resize(GTK_WINDOW(message),200,100);
		gtk_window_set_modal(GTK_WINDOW(message),TRUE);
		frame=gtk_frame_new(NULL);
		replay=gtk_button_new_with_label("Play Again");
		quit=gtk_button_new_with_label("Exit");
		label=gtk_label_new("It was a draw");
		vbox=gtk_vbox_new(0,0);
		hbox=gtk_hbox_new(1,0);
		gtk_container_add(GTK_CONTAINER(message),frame);
		gtk_container_add(GTK_CONTAINER(frame),vbox);
		gtk_box_pack_start(GTK_BOX(vbox),label,0,0,0);
		gtk_box_pack_start(GTK_BOX(vbox),hbox,0,0,0);
		gtk_box_pack_start(GTK_BOX(hbox),replay,1,1,0);
		gtk_box_pack_start(GTK_BOX(hbox),quit,1,1,0);
		g_signal_connect(GTK_OBJECT(replay),"clicked",GTK_SIGNAL_FUNC(reset),message);
		g_signal_connect(GTK_OBJECT(quit),"clicked",GTK_SIGNAL_FUNC(out),message);
		gtk_widget_show_all(message);
	}
}
		
void markit(GtkWidget *button,GtkWidget *label)
{
	char *str=(char *)gtk_label_get_label(GTK_LABEL(label));
	if(turn==0&&str[0]==0)
	{
		char turns[25];
		gtk_label_set(GTK_LABEL(label),"X");
		turn=1;
		sprintf(turns,"Player %d's turn",turn+1);
		gtk_label_set(GTK_LABEL(turn_info),turns);
	}
	else if(turn==1&&str[0]==0)
	{	char turns[25];
		gtk_label_set(GTK_LABEL(label),"0");
		turn=0;
		sprintf(turns,"Player %d's turn",turn+1);
		gtk_label_set(GTK_LABEL(turn_info),turns);
	}
	check();
}
int main(int argc,char *argv[])
{
	GtkWidget *window;
	GtkWidget *button[3][3];
	GtkWidget *vbox;
	GtkWidget *hbox[3];
	GtkWidget *frame;
	GtkWidget *separator;
	GtkWidget *menubar,*file_menu,*file,*help,*quit,*help_menu,*Reset,*About;
	char turns[15];
	int i,j;
	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"TIC TAC TOE");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),200,250);
	frame=gtk_frame_new(NULL);
	separator=gtk_hseparator_new();
	vbox=gtk_vbox_new(0,0);
	gtk_container_add(GTK_CONTAINER(window),frame);
	gtk_container_add(GTK_CONTAINER(frame),vbox);

	sprintf(turns,"Player %d's turn",turn+1);
	turn_info=gtk_label_new(turns);
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			button[i][j]=gtk_button_new_with_label(NULL);
			mark[i][j]=gtk_label_new("");
			gtk_container_add(GTK_CONTAINER(button[i][j]),mark[i][j]);
		}
	}
	
	for(i=0;i<3;i++)
	{
		hbox[i]=gtk_hbox_new(0,0);
	}
	
	gtk_box_pack_start(GTK_BOX(vbox),separator,0,0,0);
	gtk_box_pack_start(GTK_BOX(vbox),turn_info,0,0,0);
	for(i=0;i<3;i++)
	{
		gtk_box_pack_start(GTK_BOX(vbox),hbox[i],TRUE,TRUE,0);
	}
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			gtk_box_pack_start(GTK_BOX(hbox[i]),button[i][j],TRUE,TRUE,0);
		}
	}
	g_signal_connect(GTK_OBJECT(window),"destroy",gtk_main_quit,NULL);
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			g_signal_connect(GTK_OBJECT(button[i][j]),"clicked",GTK_SIGNAL_FUNC(markit),mark[i][j]);
		}
	}
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
	
