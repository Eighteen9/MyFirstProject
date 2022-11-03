#include <stdio.h>
#include <stdlib.h>

//ʹ��ջ����ǰ׺���ʽת��׺���ʽ
typedef char DataType;

//����һ����ջ---------------------����ջ���ű�ͷ���
typedef struct Stack{
    DataType data;
    struct Stack *next;
}Stack;//ע��Ҫ�ѱ����Ͷ���ı�����������

//������ջ�ĳ�ʼ��
void Stack_Initial(Stack *stack){
    stack->data='S';
    stack->next=NULL;
    printf("��ʼ���ɹ�\n");
}

//����һ����ջ�Ĳ���---ͷ����
void Stack_Creat(Stack *stack,DataType data){
    Stack *s;
    s=(Stack *)malloc((sizeof(Stack)));      //���￪��malloc((sizeof(stack))�����stack��һ��ָ�������������Զ�ֹͣ��������
    s->data=data;
    s->next=stack->next;
    stack->next=s;
    printf("����%c��ջ�ɹ�\n",data);
}

//����һ����ջ����
DataType Stack_Out(Stack *stack){
    //���ж���ջ�Ƿ�Ϊ��
    if(stack->next==NULL){
        printf("ջ��Ԫ��Ϊ��,��ջʧ��\n");
        return '0';
    }

    Stack *q=stack->next;
    DataType num=q->data;
    stack->next=q->next;
    free(q);
    printf("ջ��Ԫ��%c��ջ�ɹ�\n",num);
    return num;
}



//���巽��ʵ��ȡջ��Ԫ��
DataType Stack_Gettop(Stack *stack){
    if(stack->next==NULL){
        printf("ջ��Ԫ��Ϊ��\n");
        return 0;
    }
    Stack *p=stack->next;
    DataType num=p->data;
    printf("ջ��Ԫ��Ϊ%c\n",num);
    return num;
}

//���ﶨ����ջԪ�صı���,
void Stack_Bianli(Stack *stack){
    Stack *p=stack->next;
    printf("��ջ�е�Ԫ��Ϊ");
    while(p!=NULL){
        printf("%c",p->data);
        p=p->next;
    }
    printf("\n");
}



//����ʹ��һ���������������ȼ��ıȽ�
int compare(char str1,char str2)
{
    //�Ƚ�str1��str2�����ȼ���str1>str2��Ϊ1��  str1��str2��Ȼ�str1<str2��Ϊ-1
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

//�����������ʵ����׺���ʽת��Ϊ��׺���ʽ��Ȼ�����ú�׺���ʽ�������ݵļ���
void Stack_Counter(char str[])
{
    //char str[]={'(','3','#','+','5','#','*','6','#',')','/','(','4','#','/','2','#','+','1','#',')','\0'};
    //��׺ת��׺�Ĵ���---����������ջ
    Stack optr,postexp;
    Stack_Initial(&optr);
    Stack_Initial(&postexp);
    Stack_Creat(&optr,'#');
    Stack_Creat(&postexp,'#');
    int i=0;
    printf("----------��ʼ��ȡ��׺���ʽ��ֵ-------------\n");
    for(i; str[i]!='\0'; i++)
    {
        printf("�˴�ȡ�����ַ�Ϊ%c\n",str[i]);
        //����������ַ��Ļ�,ֱ�ӽ���׺���ʽջ -----���ֽ����ı�ʶΪ#
        if((str[i]>='0' && str[i]<='9') || str[i]=='#')
        {
            printf("ִ����if���\n");
            Stack_Creat(&postexp,str[i]);
        }
        else
        {
            printf("ִ����else���\n");
            switch(str[i])   //str[i]�ڴ˴������������������
            {
            case '('://���������ַ�Ϊ'('ֱ�ӽ������ջ
                Stack_Creat(&optr,str[i]);
                break;
            case ')'://���������ַ�Ϊ')',��ջ�е�'('֮ǰ�ķ��ŵ�����������ʽջ��
                while(Stack_Gettop(&optr)!='(')
                {
                    Stack_Creat(&postexp,Stack_Out(&optr));
                }
                printf("��(���������ջ\n");
                Stack_Out(&optr);//�˴���ʾ��ջ�е�'('Ҳ�����������ǲ�������ʽջ��
                break;
            default:
                if(Stack_Gettop(&optr)=='(' || Stack_Gettop(&optr)=='#') Stack_Creat(&optr,str[i]);//��������ջ�е�ջ��Ԫ��Ϊ'('��'#'����ôԪ�������ֱ�ӽ�ջ
                else if(compare(str[i],Stack_Gettop(&optr))==1)//���str[i]�����ȼ�����ջ��Ԫ�ص����ȼ���ֱ�ӽ�ջ��OK
                {
                    Stack_Creat(&optr,str[i]);
                }
                else //���ջ��Ԫ�ص����ȼ�����str[i],��Ҫ�ȳ�ջ��Ȼ���ٴ�ȡջ��Ԫ�ؽ��бȽ�
                {
                    printf("ִ����dafault����е�else\n");
                    Stack_Creat(&postexp,Stack_Out(&optr));
                    while(compare(str[i],Stack_Gettop(&optr))==-1 && Stack_Gettop(&optr)!='(' )
                    {
                        printf("ִ����while�ڵ����\n");
                        Stack_Creat(&postexp,Stack_Out(&optr));
                    }
                    //��ʱ��Ҫ�Ѹ�str[i]�������ջ
                    Stack_Creat(&optr,str[i]);

                }
                break;
            }
        }
    }
     printf("----------��׺���ʽ��ȡ����,��ʱ�������ջoptr��Ԫ�����γ�ջ��ջ��postexp��-------------\n");
    //��ʱ��������е�Ԫ����ջ�����ʽ��
    while(Stack_Gettop(&optr)!='#'){
        Stack_Creat(&postexp,Stack_Out(&optr));
    }
    printf("-------��ʱ��postexp��һ�������ı����õĺ�׺���ʽ-----------\n");
    printf("����postexpջ\n");
    Stack_Bianli(&postexp);




    //�˿̻�õ�һ����׺���ʽջpostexp-------����ö��д�ź�׺���ʽ����ӷ���
    //��Ҫ��postexp�е�Ԫ�����ν���ͷ�巨��һ���µ���ջpost����ʱ����ջ��ջ֮���˳����������ĺ�׺���ʽ
    printf("--------------��postexp�б����õĺ�׺���ʽ���л�ԭ-----------------\n");
    Stack post;
    Stack_Initial(&post);
    Stack *r=&postexp;
    r=r->next;
    //��ʼ���н�postexp�е�Ԫ������ͷ����post��

    while(r!=NULL){
        r=r->next;
        Stack_Creat(&post,Stack_Out(&postexp));
    }
    printf("������׺���ʽջ---post\n");
    Stack_Bianli(&post);

    //�Ժ�׺���ʽ���м���-----post-Ϊ���綨��#�ĺ�׺���ʽ
    //����׺���ʽ1#+2#+3#�õ��ĺ�׺���ʽ #1#2#+3#+  ������ջ����
    //����ջpost�е��ַ������ַ�����
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
    printf("����ch=%s,j=%d",ch,j);
    int num=0;
    //����һ������counterջ
    Stack counter;
    Stack_Initial(&counter);
    for(num;num<j;num++){
        /*�����ã����ǵ��ַ�����ֻ�ܴ洢һ���ַ����������λ�����ַ��͵����뷽��
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
        default://ʣ�µ�Ĭ�Ͼ�������
            Stack_Creat(&counter,ch);
        }
        */
    }
    int num_get=Stack_Out(&counter);
    printf("�ñ��ʽ��ֵΪ%d",num_get);
}


int main()
{

    int str[10];
    scanf("%s",str);
    int i=0;
    printf("str=%s\n",str);
    for(i;i<10;i++){
        printf("���str�е�����%c\n",str[i]);
    }
    Stack_Counter(str);
    printf("ִ�����\n");

    system("pause");


}
