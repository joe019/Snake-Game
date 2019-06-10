```c
void setBorders()
{
    ...  
}
```
![alt text](https://github.com/joe019/Snake-Game/blob/master/images/borders2dArray.png)
***

```c
void repeat()
{
    ...
    /*
    By pressing one arrow key, getch will push three values into the buffer:
            '\033'
            '['
            'A', 'B', 'C' or 'D'
    */
    if (getchar() == '\033')
    {
        getchar();      // skip the [
        key = getchar();
        controlMovement(key);
    }
    ...
}
```
***
