#include <stdio.h>
#include <stdlib.h>

//使用栈进行前缀表达式转后缀表达式
typedef char DataType;

//定义一个链栈---------------------该链栈带着表头结点
typedef struct Stack{
    DataType data;
    struct Stack *next;
}Stack;//注意要把别名和定义的变量名区别开来

//进行链栈的初始化
void Stack_Initial(Stack *stack){
    stack->data='S';
    stack->next=NULL;
    printf("初始化成功\n");
}

//创建一个入栈的操作---头插入
void Stack_Creat(Stack *stack,DataType data){
    Stack *s;
    s=(Stack *)malloc((sizeof(Stack)));      //这里开辟malloc((sizeof(stack))这里的stack是一个指针变量，程序会自动停止，不报错
    s->data=data;
    s->next=stack->next;
    stack->next=s;
    printf("数据%c入栈成功\n",data);
}

//定义一个出栈操作
DataType Stack_Out(Stack *stack){
    //先判断链栈是否为空
    if(stack->next==NULL){
        printf("栈顶元素为空,出栈失败\n");
        return '0';
    }

    Stack *q=stack->next;
    DataType num=q->data;
    stack->next=q->next;
    free(q);
    printf("栈顶元素%c出栈成功\n",num);
    return num;
}



//定义方法实现取栈顶元素
DataType Stack_Gettop(Stack *stack){
    if(stack->next==NULL){
        printf("栈顶元素为空\n");
        return 0;
    }
    Stack *p=stack->next;
    DataType num=p->data;
    printf("栈顶元素为%c\n",num);
    return num;
}

//这里定义链栈元素的遍历,
void Stack_Bianli(Stack *stack){
    Stack *p=stack->next;
    printf("链栈中的元素为");
    while(p!=NULL){
        printf("%c",p->data);
        p=p->next;
    }
    printf("\n");
}



//单独使用一个方法来进行优先级的比较
int compare(char str1,char str2)
{
    //比较str1和str2的优先级，str1>str2则为1，  str1和str2相等或str1<str2则为-1
    if(str1==str2) return -1;
    switch(str1)
    {
        case '+':if(str2=='*' || str2=='/' || str2=='-') return -1;else return 1;break;
        case '-':if(str2=='*' || str2=='/' || str2=='+') return -1;else return 1;break;
        case '*':if(str2=='+' || str2=='-' || str2=='#') return 1;else return -1;break;
        case '/':if(str2=='+' || str2=='-' || str2=='#') return 1;else return -1;break;
        default : break;
    }
}

//在这个方法中实现中缀表达式转化为后缀表达式，然后利用后缀表达式进行数据的计算
void Stack_Counter(char str[])
{
    //char str[]={'(','3','#','+','5','#','*','6','#',')','/','(','4','#','/','2','#','+','1','#',')','\0'};
    //中缀转后缀的处理---创建两个链栈
    Stack optr,postexp;
    Stack_Initial(&optr);
    Stack_Initial(&postexp);
    Stack_Creat(&optr,'#');
    Stack_Creat(&postexp,'#');
    int i=0;
    printf("----------开始读取中缀表达式的值-------------\n");
    for(i; str[i]!='\0'; i++)
    {
        printf("此次取出的字符为%c\n",str[i]);
        //如果是数字字符的话,直接进后缀表达式栈 -----数字结束的标识为#
        if((str[i]>='0' && str[i]<='9') || str[i]=='#')
        {
            printf("执行了if语句\n");
            Stack_Creat(&postexp,str[i]);
        }
        else
        {
            printf("执行了else语句\n");
            switch(str[i])   //str[i]在此处都是运算符或者括号
            {
            case '('://如果输入的字符为'('直接进运算符栈
                Stack_Creat(&optr,str[i]);
                break;
            case ')'://如果输入的字符为')',把栈中的'('之前的符号弹出来放入表达式栈中
                while(Stack_Gettop(&optr)!='(')
                {
                    Stack_Creat(&postexp,Stack_Out(&optr));
                }
                printf("将(弹出运算符栈\n");
                Stack_Out(&optr);//此处表示把栈中的'('也弹出来，但是不放入表达式栈中
                break;
            default:
                if(Stack_Gettop(&optr)=='(' || Stack_Gettop(&optr)=='#') Stack_Creat(&optr,str[i]);//如果运算符栈中的栈顶元素为'('或'#'，那么元素运算符直接进栈
                else if(compare(str[i],Stack_Gettop(&optr))==1)//如果str[i]的优先级高于栈顶元素的优先级，直接进栈就OK
                {
                    Stack_Creat(&optr,str[i]);
                }
                else //如果栈顶元素的优先级高于str[i],需要先出栈。然后再次取栈顶元素进行比较
                {
                    printf("执行了dafault语句中的else\n");
                    Stack_Creat(&postexp,Stack_Out(&optr));
                    while(compare(str[i],Stack_Gettop(&optr))==-1 && Stack_Gettop(&optr)!='(' )
                    {
                        printf("执行了while内的语句\n");
                        Stack_Creat(&postexp,Stack_Out(&optr));
                    }
                    //此时需要把该str[i]入运算符栈
                    Stack_Creat(&optr,str[i]);

                }
                break;
            }
        }
    }
     printf("----------中缀表达式读取结束,此时将运算符栈optr中元素依次出栈入栈到postexp中-------------\n");
    //此时把运算符中的元素入栈到表达式中
    while(Stack_Gettop(&optr)!='#'){
        Stack_Creat(&postexp,Stack_Out(&optr));
    }
    printf("-------此时的postexp是一个完整的被逆置的后缀表达式-----------\n");
    printf("遍历postexp栈\n");
    Stack_Bianli(&postexp);




    //此刻会得到一个后缀表达式栈postexp-------如果用队列存放后缀表达式会更加方便
    //需要将postexp中的元素依次进行头插法到一个新的链栈post，此时的链栈出栈之后的顺序才是真正的后缀表达式
    printf("--------------将postexp中被逆置的后缀表达式进行还原-----------------\n");
    Stack post;
    Stack_Initial(&post);
    Stack *r=&postexp;
    r=r->next;
    //开始进行将postexp中的元素依次头插在post中

    while(r!=NULL){
        r=r->next;
        Stack_Creat(&post,Stack_Out(&postexp));
    }
    printf("遍历后缀表达式栈---post\n");
    Stack_Bianli(&post);

    //对后缀表达式进行计算-----post-为含界定符#的后缀表达式
    //对中缀表达式1#+2#+3#得到的后缀表达式 #1#2#+3#+  进行链栈计算
    //把链栈post中的字符付给字符数组
    DataType ch[100];

    Stack *L=&post;
    L=L->next;
    int j=0;
    while(L!=NULL)
    {
        L=L->next;
        ch[j]=Stack_Out(&post);
        j++;
    }
    printf("输入ch=%s,j=%d",ch,j);
    int num=0;
    //创建一个计算counter栈
    Stack counter;
    Stack_Initial(&counter);
    for(num;num<j;num++){
        /*不可用，考虑到字符数组只能存储一个字符，如果是两位数的字符就得另想方法
        switch(ch[num])
        {
        case '#':
            Stack_Out(&post);
            break;
        case '+':
            int a,b,c;
            a=(int)Stack_Out(&counter);
            b=(int)Stack_Out(&counter);
            c=a+b;
            Stack_Creat(&counter,c);
            break;
        case '-':
            int a,b,c;
            a=(int)Stack_Out(&counter);
            b=(int)Stack_Out(&counter);
            c=a-b;
            Stack_Creat(&counter,(DataType)c);
            break;
        case '*':
            int a,b,c;
            a=(int)Stack_Out(&counter);
            b=(int)Stack_Out(&counter);
            c=a*b;
            Stack_Creat(&counter,(DataType)c);
            break;
        case '/':
            int a,b,c;
            a=(int)Stack_Out(&counter);
            b=(int)Stack_Out(&counter);
            c=a/b;
            Stack_Creat(&counter,(DataType)c);
            break;
        default://剩下的默认就是数字
            Stack_Creat(&counter,ch);
        }
        */
    }
    int num_get=Stack_Out(&counter);
    printf("该表达式的值为%d",num_get);
}


int main()
{

    int str[10];
    scanf("%s",str);
    int i=0;
    printf("str=%s\n",str);
    for(i;i<10;i++){
        printf("输出str中的数据%c\n",str[i]);
    }
    Stack_Counter(str);
    printf("执行完毕\n");

    system("pause");


}
