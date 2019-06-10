
// Set four borders within which the snake can move
void set_borders()
{
    int i;
    
    // horizontal borders
    for(i=0; i<=49; i++)
    {
        borders[0][i]=1;    // top border
        borders[24][i]=1;   // bottom border   
    }

    // vertical borders
    for(i=1; i<=23; i++)
    {
        borders[i][0]=1;    // left border
        borders[i][49]=1;   // right border   
    }        
}

borders
(0,0) (0,1) (0,2) ... (0,49)
.
.
.
(24,0) (24,1) ... (24,49)

if(_kbhit())   /// If keyboard hit
{
    /*
    By pressing one arrow key getch will push three values into the buffer:

            '\033'
            '['
            'A', 'B', 'C' or 'D'
    */
    if (getchar() == '\033')
    {
        getchar(); // skip the [
    }
k = getchar();
reaction_on_keyboard(k);
}

https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/