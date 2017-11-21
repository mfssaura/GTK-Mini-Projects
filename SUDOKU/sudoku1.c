#include<stdio.h>
#include<stdlib.h>
#include<gtk/gtk.h>
int number=0,start=0;
int nrow[81];
int ncol[81];

GtkWidget* sudoku[9][9];
int ques_arr[9][9];
int sol_arr[9][9];
void put_value(GtkWidget *win,int n)
{
    int i,j;
    i=n/9;
    j=n%9;
    char* c=gtk_entry_get_text (sudoku[i][j]);
    int val=atoi(c);
    if(val>9)
    {
       val=val%10;
       char temp[10];
       sprintf (temp, "%d", (int)val);
       gtk_entry_set_text (sudoku[i][j],temp);
    }
    ques_arr[i][j]=val;
}
GtkEntry* CreateButton (GtkWidget *table, int row, int column)
{
    GtkWidget *entry;

    entry = gtk_entry_new();
    gtk_widget_set_usize(GTK_WIDGET(entry),20,20);

    gtk_signal_connect (GTK_OBJECT (entry), "changed",
                        G_CALLBACK(put_value), (row*9+column));

    gtk_table_attach (GTK_TABLE (table), entry,
                      column, column+1,
                      row, row + 1,
                      GTK_FILL | GTK_EXPAND,
                      GTK_FILL | GTK_EXPAND,
                      1, 1);

    return entry;
}
void construct(GtkWidget *table)
{
    int i=0,k=0,j=0;
    for(i=0;i<9;i++)
    {
       for(j=0;j<9;j++)
       {
           sudoku[i][j]=CreateButton(table,i,j);
       }
    }
}



int isAvailable(int sudoku[][9], int row, int col, int num)
{
    int i, j;
    for(i=0; i<9; ++i)
        if( (sudoku[row][i] == num) || ( sudoku[i][col] == num )  )
            return 0;
    int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;
    for(i=rowStart; i<(rowStart+3); ++i)
    {
        for(j=colStart; j<(colStart+3); ++j)
        {
            if( sudoku[i][j] == num )
                return 0;
        }
    }   

    return 1;
}    

int fillsudoku(int sudoku[][9], int row, int col)
{
    int i;
    if( row<9 && col<9 )
    {
        if( sudoku[row][col] != 0 )
        {
            if( (col+1)<9 )
                return fillsudoku(sudoku, row, col+1);
            else if( (row+1)<9 )
                return fillsudoku(sudoku, row+1, 0);
            else
                return 1;
        }
        else
        {
            for(i=0; i<9; ++i)
            {
                if( isAvailable(sudoku, row, col, i+1) )
                {
                    sudoku[row][col] = i+1;
                    nrow[number]=row;
                    ncol[number]=col;
                    number++;    
                    if( (col+1)<9 )
                    {
                    if( fillsudoku(sudoku, row, col +1) )
                        return 1;
                        else
                          {
                           number--;
                            nrow[number]=0;
                            ncol[number]=0; 
                           sudoku[row][col] = 0;
                    }}
                    else if( (row+1)<9 )
                    {
                        if( fillsudoku(sudoku, row+1, 0) )    
                            return 1;
                        else
                          {  sudoku[row][col] = 0;
                            number--;
                            nrow[number]=0;
                            ncol[number]=0; 
		    }     }
                    else
                        return 1;
                }
            }
        }
        return 0;
    }
    else
    {
        return 1;
    }
} 



void create_game(GtkWidget *wid,gpointer data)
{
    int temp_arr[9][9];
    FILE *fp, *ft ;
    long int recsize ;
    int i,j;
    fp = fopen ( "puzzle_store.DAT", "rb+" ) ;
     if ( fp == NULL )
     {
          fp = fopen ( "puzzle_store.DAT", "wb+" ) ;
          if ( fp == NULL )
          {
                 puts ( "Cannot open file" ) ;

          }
     }


     recsize = sizeof (temp_arr) ;
     srand(time(NULL));
     int pno = rand()%13+1;
     pno*=2;
     if(pno==10)
     pno=11;
     rewind ( fp ) ;
     for(i=0;i<pno;i++)
        fread ( &temp_arr, recsize, 1, fp );
     for(i=0;i<9;i++)
     {
         for(j=0;j<9;j++)
         { 
             gtk_editable_set_editable (GTK_EDITABLE (sudoku[i][j]),1);
         }
     }
     for(i=0;i<81;i++)
     {
        nrow[i]=0;
        ncol[i]=0;
     }
     number=0;
     start=0;
     for(i=0;i<9;i++)
     {
        for(j=0;j<9;j++)
        {
           ques_arr[i][j]=temp_arr[i][j];
           sol_arr[i][j]=temp_arr[i][j];
           if(ques_arr[i][j]==0)
           {
               gtk_entry_set_text (sudoku[i][j]," ");
               continue;
           }
           char temp[10];
           sprintf (temp, "%d", (int)ques_arr[i][j]);
           gtk_entry_set_text (sudoku[i][j],temp);
           gtk_editable_set_editable (GTK_EDITABLE (sudoku[i][j]),0);
        }
     }
     fillsudoku(sol_arr, 0, 0);
}



void solve_game(GtkWidget *wid,gpointer data)
{

    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
             char temp[10];
             sprintf (temp, "%d", (int)sol_arr[i][j]);
             gtk_entry_set_text (sudoku[i][j],temp);
        }
    }
}


void check_game(GtkWidget *wid,GtkWidget* data)
{
     int i,j,k;
     for(i=0;i<9;i++)
     {
         for(j=0;j<9;j++)
         {
            for(k=j+1;k<9;k++)
            {
                  if(ques_arr[i][j]==ques_arr[i][k])
                  {
                     gtk_label_set_text(data,"Wrong");
                     return;
                   }
            }
         } 
      }

      for(i=0;i<9;i++)
      {
          for(j=0;j<9;j++)
          {
              for(k=j+1;k<9;k++)
              {
                   if(ques_arr[j][i]==ques_arr[k][i])
                   {
                       gtk_label_set_text(data,"Wrong");
                       return;
                   }
              }
          }
       }

     gtk_label_set_text(data,"Correct,done!");
}

 
void give_hint(GtkWidget* win, gpointer data)
{
     if(start >= number)
     return;
     while(ques_arr[nrow[start]][ncol[start]]!=0)
     {
          if(start==number)
          return;
          start++;
     }
     ques_arr[nrow[start]][ncol[start]]=sol_arr[nrow[start]][ncol[start]];
     char temp[10];
     sprintf (temp, "%d", (int)ques_arr[nrow[start]][ncol[start]]);
     gtk_entry_set_text (sudoku[nrow[start]][ncol[start]],temp);
}

int main(int argc, char *argv[])
{
GtkWidget *window,*label,*hbox,*vbox,*table,*start,*check,*solve,*hint,*exit;
    gtk_init(&argc,&argv);
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(window,250,500);
    gtk_window_set_title (GTK_WINDOW (window), "SUDOKU");
    table=gtk_table_new(9,9,TRUE);
    construct(table);
    int i;
    vbox=gtk_vbox_new(FALSE,1);

        GtkWidget *separator,*button,*menu,*file_menu,*help_menu,*menu_bar;
        vbox=gtk_vbox_new(0,0);
        menu=gtk_menu_new();
        menu_bar=gtk_menu_bar_new();
        file_menu=gtk_menu_item_new_with_label("File");
	label=gtk_label_new(" ");

        
        
                GtkWidget* menu_item=gtk_menu_item_new_with_label("New Game");
                gtk_menu_shell_append(GTK_MENU_SHELL(menu),menu_item);
                g_signal_connect(menu_item,"activate",G_CALLBACK(create_game),window);


		menu_item=gtk_menu_item_new_with_label("Solve");
                gtk_menu_shell_append(GTK_MENU_SHELL(menu),menu_item);
                g_signal_connect(menu_item,"activate",G_CALLBACK(solve_game),window);

		menu_item=gtk_menu_item_new_with_label("Exit");
                gtk_menu_shell_append(GTK_MENU_SHELL(menu),menu_item);
                g_signal_connect(menu_item,"activate",G_CALLBACK(gtk_main_quit),window);


        
        gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_menu),menu);
        gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar),file_menu);
	gtk_box_pack_start(GTK_BOX(vbox),menu_bar,0,0,0);


    //start=gtk_button_new_with_label("NEW GAME");
    check=gtk_button_new_with_label("CHECK");
    //solve=gtk_button_new_with_label("SOLVE");
    hint=gtk_button_new_with_label("AUTOMATIC TURN/HELP");
    exit=gtk_button_new_with_label("LEAVE GAME");


GdkColor color1;
    gdk_color_parse ("green", &color1);
    gtk_widget_modify_bg(GTK_WIDGET(hint), GTK_STATE_NORMAL, &color1);
    GdkColor color2;
    gdk_color_parse ("red", &color2);
    gtk_widget_modify_bg(GTK_WIDGET(exit), GTK_STATE_NORMAL, &color2);
    GdkColor color3;
    gdk_color_parse ("yellow", &color3);
    gtk_widget_modify_bg(GTK_WIDGET(check), GTK_STATE_NORMAL, &color3);

    label=gtk_label_new(" ");
    g_signal_connect(G_OBJECT(check),"clicked",G_CALLBACK(check_game),label);
    g_signal_connect(G_OBJECT(hint),"clicked",G_CALLBACK(give_hint),NULL);
    g_signal_connect(G_OBJECT(exit),"clicked",G_CALLBACK(gtk_main_quit),NULL);
    gtk_box_pack_start(GTK_BOX(vbox),table,TRUE,TRUE,5);
    /*gtk_box_pack_start(GTK_BOX(vbox),start,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(vbox),solve,TRUE,TRUE,5);*/
    gtk_box_pack_start(GTK_BOX(vbox),check,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(vbox),hint,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(vbox),label,TRUE,TRUE,5);
    gtk_box_pack_start(GTK_BOX(vbox),exit,TRUE,TRUE,5);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
