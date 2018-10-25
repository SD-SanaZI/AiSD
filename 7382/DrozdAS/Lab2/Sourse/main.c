#include <stdio.h>
#include <stdlib.h>

struct binkor                                                                                 //Структура бинарного коромысла(Далее БинКор)
{
	struct plecho* left;
	struct plecho* right;
	struct binkor* head;
};

struct plecho                                                                                //Структура плеча
{
	int length;
	int weight;
	struct binkor* wei;
};

void maker(char* str,struct binkor* a)      // Создает список бинарных коромысел
{
	char* simvol=str;      //Счетчик, с помощью которого мы понимаем на каком символе сейчас находимся
	short count1=0;        //Переменная для считывания Длины/Груза
	int exit=0;            //Переменная для прохода БинКор
	while(*simvol=='(')    //Доходим до Длины
		simvol++;
	while(*simvol!=' ')    //Посимвольно считаем Длину
	{
		count1=count1*10+*simvol-'0';
		simvol++;
	}
	a->left->length=count1;   //Записываем данные в структуру
	simvol++;
	if(*simvol=='(')          //Если Груз это БинКор
	{
		struct binkor *c=(struct binkor *)calloc(1,sizeof(struct binkor));      //Создаем новую структуру БинКор
        c->head=a;
	    struct plecho* l=(struct plecho *)calloc(1,sizeof(struct plecho));
	    struct plecho* r=(struct plecho *)calloc(1,sizeof(struct plecho));
	    c->left=l;
	    c->right=r;
	    maker(simvol,c);        //Заполняем созданную структуру
		a->left->weight=-1;     //Так как Груз является БинКор а не Гирькой, впишем в вес невозможное число веса Гирьки
		a->left->wei=c;         //Т.к weight не обозначает вес Гирьки, то считаем вес через БинКор(вписываем в wei адрес этого БинКор)
	    while(exit!=-1)         //Цикл прохода БинКор
	    {
	        if(*simvol=='(')
	    	    exit++;
	        if(*simvol==')')
	        	exit--;
	        simvol++;
        }
	}
	else                          //Если груз это Гирька
	{
		count1=0;
		while(*simvol!=')')       //Пока не посчитаем Груз
		{
			count1=count1*10+*simvol-'0';
			simvol++;
		}
		a->left->weight=count1;   //Записываем данные в структуру
		a->left->wei=NULL;        //Т.к. Груз не БинКор адрес делаем пустым
	}
	simvol++;
	while(*simvol=='(')           //Доходим до Длины
		simvol++;
	count1=0;
	while(*simvol!=' ')           //Посимвольно считаем Длину
	{
		count1=count1*10+*simvol-'0';
		simvol++;
	}
	simvol++;
	a->right->length=count1;      //Записываем данные в структуру
	if(*simvol=='(')              //Если Груз это БинКор
	{
		struct binkor *c=(struct binkor *)calloc(1,sizeof(struct binkor));   //Создаем новую структуру БинКор
        c->head=a;
	    struct plecho* l=(struct plecho *)calloc(1,sizeof(struct plecho));
	    struct plecho* r=(struct plecho *)calloc(1,sizeof(struct plecho));
	    c->left=l;
	    c->right=r;
	    maker(simvol,c);      //Заполняем созданную структуру
		a->right->weight=-1;  //Так как Груз является БинКор а не Гирькой, впишем в вес невозможное число веса Гирьки
		a->right->wei=c;      //Т.к weight не обозначает вес Гирьки, то считаем вес через БинКор(вписываем в wei адрес этого БинКор)
		                      //Во второй раз не пишем цикл прохода БинКор т.к. уверены в правильности Введенного Бинарного коромысла и после Груза правого плеча не может быть ничего нужного
	}
	else                      //Если груз это Гирька
	{
		count1=0;
		while(*simvol!=')')   //Пока не посчитаем Груз
		{
			count1=count1*10+*simvol-'0';
			simvol++;
		}
		a->right->weight=count1;   //Записываем данные в структуру
		a->right->wei=NULL;        //Т.к. Груз не БинКор адрес делаем пустым
	}
}

int are_correct(char* str)// Проверяет на корректность БинКор
{
	char* simvol=str;     //Счетчик, с помощью которого мы понимаем на каком символе сейчас находимся
	int count=0;          //Переменная для прохода Длины/Груза
	int exit=0;           //Переменная для прохода БинКор
	
	if(*(simvol+1)=='(' && *simvol=='(')    //если БинКор
	{
		simvol=str+2;
		while(*simvol>='0' && *simvol<='9') //Проверяем есть ли Длина
		{
			count++;
			simvol++;
		}
		if(count==0)                        //Если нет Длины возвращаем ошибку
			return 1;
		if(*simvol!=' ')                    //Если между Длинной и Грузом нет пробела возвращаем ошибку
			return 2;
		simvol++;
		if((*(simvol+1)!='(' || *simvol!='(') && (*simvol<'0' || *simvol>'9'))  //Если Груз не БинКор и не Гирька возвращаем ошибку
			return 3;
		if(*(simvol+1)=='(' || *simvol=='(') //Если груз это БинКор,рекурсивно проверяем на коректность этот БинКор
		{
			count=are_correct(simvol);
			if(count!=0)                     //Если в рекурсивно проверенном БинКор есть ошибка возвращаем ошибку
				return count;                
		}
		count=0;
		if(*simvol>='0' && *simvol<='9')
		{
		    char* sim=simvol;                //Переменная для возвращения к началу Груза
		    while(*simvol>='0' && *simvol<='9') //Проверяем есть ли Длина
		    {
	    		count++;
	    		simvol++;
	    	}
	    	if(*simvol!=')')
	    	    return 3;
	    	simvol=sim;
		}
        while(exit!=-1)                      //Цикл прохода Груза
	    {
	    	if(*simvol=='(')
	    		exit++;
	    	if(*simvol==')')
	    		exit--;
	    	simvol++;
	    }
		if(*simvol!='(')                     //Если не открыто Плечо возвращаем ошибку
			return 5;
		simvol++;
		count=0;
		while(*simvol>='0' && *simvol<='9')  //Проверяем есть ли Длина
        {
                count++;
                simvol++;
        }
        if(count==0)                         //Если нет Длины возвращаем ошибку
                return 6;
        if(*simvol!=' ')                     //Если между Длиной и Грузом нет пробела возвращаем ошибку
                return 7;
        simvol++;
        if((*(simvol+1)!='(' || *simvol!='(') && (*simvol<'0' || *simvol>'9'))  //Если Груз не БинКор и не Гирька возвращаем ошибку
                return 8;
        if(*(simvol+1)=='(' || *simvol=='(') //Если груз это БинКор,рекурсивно проверяем на коректность этот БинКор
		{
                count=are_correct(simvol);
				if(count!=0)                 //Если в рекурсивно проверенном БинКор есть ошибка возвращаем ошибку
					return count;
		}
		count=0;
		if(*simvol>='0' && *simvol<='9')
		{
		    char* sim=simvol;                //Переменная для возвращения к началу Груза
		    while(*simvol>='0' && *simvol<='9') //Проверяем есть ли Длина
		    {
	    		count++;
	    		simvol++;
	    	}
	    	if(*simvol!=')')
	    	    return 3;
	    	simvol=sim;
		}
		exit=0;
        while(exit!=-1)                      //Цикл прохода Груза
	    {
	    	if(*simvol=='(')
	    		exit++;
	    	if(*simvol==')')
	    		exit--;
	    	simvol++;
    	}
		if(*simvol!=')')                     //Если БинКор не закрыт возвращаем ошибку
			return 10;
		return 0;
	}
	else
	    if(*(simvol)!='(')
	        return 11;
	    else
	        return 12;
}

void destroy(struct binkor*a)   //Высвобождает память всего списка БинКор
{
    if(a->left->wei!=NULL)      //Если вместо левого Груза использовалось БинКор
        destroy(a->left->wei);
    free(a->left);
    if(a->right->wei!=NULL)     //Если вместо правого Груза использовалось БинКор
        destroy(a->right->wei);
    free(a->right);
    free(a);
}

int how_many_recurs(struct binkor* a)
{
	int count=0;
	while(a->head!=NULL)
	{
		count++;
		a=a->head;
	}
	return count;
}

short Length(struct binkor a)              //Считает Длину всех Плеч БинКор
{
	int count_to_rec=-1;					//Переменная для подсчета глубины рекурсии
	int indent;								//Счетчик для создания отступов;
	short count=0;                          //Переменная для подсчета Длины
	count=count+a.left->length;
	count_to_rec=how_many_recurs(&a);		//Посчитаем глубину рекурсии
	indent=count_to_rec;
	while(indent!=0)						//Выставим нужное количество отступов
	{
		printf("	");
		indent--;
	}
	printf("Длинна левого Плеча БинКор %d-ого по глубине равна %d.\n",count_to_rec,count);
	if(a.left->wei!=NULL)                  //Если вместо левого Груза использовалось БинК
	{
		count=count+Length(*(a.left->wei));
	}
	count=count+a.right->length;
	indent=count_to_rec;
	while(indent!=0)							//Выставим нужное количество отступов
	{
		printf("	");
		indent--;
	}
	printf("Длинна правого Плеча БинКор %d-ого по глубине равна %d.\n",count_to_rec,a.right->length);
	if(a.right->wei!=NULL)                 //Если вместо правого Груза использовалось БинКор
	{
		count=count+Length(*(a.right->wei));
	}
	return count;
}

int main()
{
int result;                                 // переменная, в которую выведется результат рекурсии
char str[100];                              //строка, для считывания данных
printf("Введите выражение.\nБинКор = (<Плечо><Плечо>)\nПлечо = (<Длина> <Груз>)\nГруз = <Гирька>(число) или <БинКор>\n");
printf("Между Плечьми нет пробелов.\nДлину и Груз отделяет пробе(и ни что другое).\nМаксимальныя длинна БинКор 100 символов.\n");
printf("Если после верного Бинарного Коромысла вы введете мусор, программа его проигнорирует.\n");
fgets(str,100,stdin);                       //Считываение предпологаемого БинКор
result=are_correct(str);                    //Проверка БинКор на корректность
if(result==0)
	printf("Выражение является Бинарным Коромыслом.\n\n");
if(result!=0)
	printf("Выражение не является Бинарным Коромыслом.\n");
if(result==1)
	printf("В левом Плече нет Длины.\n"); 
if(result==2)
	printf("Между Длиной и Грузом левого Плеча не пробел(или груза нет вообще).\n");
if(result==3)
	printf("Левый груз не БинКор и не Гирька(или не закрыто левое плечо).\n");
if(result==5)
	printf("После левого Плеча не идет правое Плечо.\n");
if(result==6)
 printf("В правом плече нет Длины.\n");
if(result==7)
 printf("Между Длиной и Грузом правого Плеча не пробел(или груза нет вообще).\n");
if(result==8)
 printf("Правый Груз не БинКор и не Гирька.\n");
if(result==10)
 printf("БинКор не закрыт.");
if(result==11)
 printf("БинКор не открыт."); 
if(result==12)
 printf("Левое плечо не открыто."); 
if(result==0)                               //Если БинКор корректно
{
    struct binkor *c=(struct binkor *)calloc(1,sizeof(struct binkor)); //Создание структуры БинКор
    c->head=NULL;
	struct plecho* l=(struct plecho *)calloc(1,sizeof(struct plecho));
	struct plecho* r=(struct plecho *)calloc(1,sizeof(struct plecho));
	c->left=l;
	c->right=r;
    maker(str,c);                   //Создание списка БинКор
    printf("\nДлина плеч Бинарного коромысла %d.",Length(*c));     //Вывод результата подсчета Длины Плеч БинКор
    destroy(c);                     //Высвобождение динамической памяти
}
}
