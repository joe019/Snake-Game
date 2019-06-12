```c
void setBorders()
{
    ...  
}
```
This function sets `borders[25][50]` as follows:<br>
![alt text](https://github.com/joe019/Snake-Game/blob/master/images/borders2dArray.png)

***

```c
void delayBF(int delay)
{
    clock_t delayEnds;

    delayEnds = clock() + delay * 1000;

    while (clock() < delayEnds)
    {
        // Do nothing
    }
}
```
`clock_t clock(void)` returns the number of clock ticks elapsed since the beginning of a program. To get the result in seconds,   divide it by `CLOCKS_PER_SEC`. [clocks / (clocks/s) = s]
***

```c
void repeat()
{
    ...
    /*
    By pressing any arrow key, following three values will be pushed into buffer:
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
References: <br>
[C library function - clock()](https://www.tutorialspoint.com/c_standard_library/c_function_clock.htm) <br>
[getch and arrow codes](https://stackoverflow.com/questions/10463201/getch-and-arrow-codes)
