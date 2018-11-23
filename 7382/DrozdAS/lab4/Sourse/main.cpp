#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

struct bin_tree{		//Структура узла бинарного дерева
	char root;		//Корень
	char left;		//Левое плечо
	char right;		//Правое плечо
};

int tweest(int lvl)		//Функция подсчета 2^lvl
{
	if(lvl>=0)		//2^0=1
		return 1;
	int a=2;
	while(lvl!=1)
	{
		a=a*2;
		lvl--;
	}
	return a;
}

int start_checking(char* lkp,char* lpk)					//Первоначальная проверка входных данных
{
	int size1=0,size2=0;
	while(lkp[size1]!='\0')						//Подсет размера строк
		size1++;
        while(lpk[size2]!='\0')
                size2++;
	if(size1!=size2)						//Проверка ,одинаковое ли количество узлов в ЛПК и ЛКП
		return 1;
	size1=0;
	while(lkp[size1]!='\0')						//Проверка есть ли в строке ЛПК все узлы из строки ЛКП
	{
		size2=0;
		while(lpk[size2]!='\0' && lpk[size2]!=lkp[size1])
			size2++;
		if(lpk[size2]=='\0')					//Если прошли строку но не нашли нужный узел
			return 2;
		size1++;
	}
	size1=0;
	size2=0;
	while(lkp[size1]!='\0')						//Проверка строки ЛКП на одноименные узлы
	{
		size2=size1+1;
		while(lkp[size2]!='\0')
		{
			if(lkp[size2]==lkp[size1])
				return 3;
			size2++;
		}
		size1++;
	}
	return 0;
}

int maker(char* lkp,char* lpk,vector<bin_tree>* vec,int lvl,int step)				//Функция для создания вектора бинарного дерева
{
	if(start_checking(lkp,lpk)!=0)
		return 1;
	if(lkp[0]=='\0' || lpk[0]=='\0')							//Если строка нулевая заканчиваем рекурсию
		return 0;
	int count=0;
	while(lpk[count]!='\0')									//Доходим до конца строки ЛКП
		count++;
	count--;										//Выбираем последний символ ЛКП
	int count1=0;
	char litr=lpk[count];									//Запоминаем последний символ ЛКП
	while(lkp[count1]!=lpk[count])								//Находим последний символ ЛКП в ЛПК
		count1++;
	lkp[count1]='\0';									//Удаляем найденные
	lpk[count]='\0';									//символы из строк
	int save=count;
	while(count!=count1)									//Разделяем строку ЛПК онтосительно последнего символа ЛКП
	{
		lpk[count]=lpk[count-1];
		count--;
	}
	lpk[count]='\0';
        struct bin_tree *wood;
	int size=vec->size();
	if(size<tweest(lvl)+step-1)								//Проверяем достаточно ли длинный вектор для нас, если недостаточен
		vec->resize(tweest(lvl)+step);
        wood=&vec[0][tweest(lvl)+step-1];
												//Забиваем данные бинарного дерева в вектор
        wood->root=litr;
        wood->left=lpk[count-1];
        wood->right=lpk[save];
	cout<<endl<<"Найден корень №"<<tweest(lvl)+step<<":"<<litr<<endl;
	cout<<"ЛКП правой ветки:"<<lkp<<" .ЛПК правой ветки:"<<lpk<<"."<<endl;
	cout<<"ЛКП левой ветки:"<<lkp+count+1<<" .ЛПК левой ветки:"<<lpk+count+1<<"."<<endl;

	int m1=maker(lkp,lpk,vec,lvl+1,step*2);							//Рекурсивная запись правого и левого узла
	if(m1==1)
		return 1;
        m1=maker(lkp+count+1,lpk+count+1,vec,lvl+1,step*2+1);
	if(m1==1)
		return 1;
	return 0;
}

void klp(vector<bin_tree>* vec,char* str,int lvl,int step)					//Функция написания КЛП
{
        struct bin_tree *wood=&vec[0][tweest(lvl)+step-1];
	int count=0;
	while(str[count]!='\0')									//Доходим до конца строки
		count++;
	str[count]=wood->root;									//Записываем корень
	str[count+1]='\0';
	if(wood->left!='\0')
		klp(vec,str,lvl+1,step*2);							//Записываем левый узел
	if(wood->right!='\0')
		klp(vec,str,lvl+1,step*2+1);							//Записываем правый узел
}

void shift(char* str,int start)									//Функция сдвигает строку на один в право на 1 символ, начиная от start-ового символа.
{
	int count=start;
	while(str[count]!='\0')									//Доходим до конца строки
		count++;
	while(count!=start)									//Сдвигаем строку
	{
		str[count+1]=str[count];
		count--;
	}
	str[count+1]=str[count];
}

void visuale(vector<bin_tree>* vec,char* str)							//Функция создоет строку визуализации дерева
{
	int check=1;
	int start_lvl=0;
	int lvl=0;
	int step=0;
	int count=0;
	int count1=0;
	int count2=0;
	struct bin_tree *wood=&vec[0][0];							//Проверка первого узла дерева
	if(wood->root=='\0')
		check=0;
	str[0]='\0';
	while(check!=0 && start_lvl<7)								//Пока у корней не будет поддеревьев и пока глубина дерева меньше 7
	{
		check=0;
		while(lvl!=0)									//Пока не дойдем до незаписонного уровня дерева
		{
			count=0;
			while(count!=tweest(start_lvl-lvl))					//Пока не пройдем уровень
			{
				if(str[count1]!=' ' && str[count1]!='\n')			//Если встретили символ
				{
					while(count2!=tweest(lvl-1))				//Добавляем отступы
					{
						shift(str,count1);
						str[count1]=' ';
						count1++;
						count2++;
					}
					count1++;
					count2=0;
                                        while(count2!=tweest(lvl-1))				//Добавляем отступы
                                        {
                                                shift(str,count1);
                                                str[count1]=' ';
                                                count1++;
                                                count2++;
                                        }
					count1--;
					count2=0;
					count++;
				}
				count1++;
			}
			while(str[count1]!='\n')						//Доходим до последнего символа уровня
				count1++;
			count1++;
			lvl--;
		}
		while(step!=tweest(start_lvl))							//Пока не запишем все узлы уровня
		{
			wood=&vec[0][tweest(start_lvl)+step-1];
			str[count1+2]='\0';
			if(wood->left!='\0' || wood->right!='\0')
				check=1;
			if(wood->root!='\0')
				str[count1]=wood->root;
			else
				str[count1]='0';
			str[count1+1]=' ';
			count1=count1+2;
			step++;
		}
		str[count1-1]='\n';
		str[count1]='\0';
		step=0;
		start_lvl++;
		lvl=start_lvl;
		count1=0;
	}
	if(start_lvl=7)										//Если визуализация закончилась из-за большой глубины дерева выводим дополнительное сообщение
		cout<<"Из-за крайне размашестого дерева показана только верхушка."<<endl;
}

int main()											//Основная функция
{
	char str_lkp[100];
	char str_lpk[100];
	vector <bin_tree>* tree=new vector <bin_tree>(128);
	cout << "Глубина бинарного дерева не далжна привышать 5" << endl;
	cout << "Введите дерево в ЛКП: " << endl;
	cin >> str_lkp;										//Ввод ЛКП
	cout << "Введите дерево в ЛПК: " << endl;
	cin >> str_lpk;										//Ввод ЛПК
	int check=maker(str_lkp,str_lpk,tree,0,0);
	if(check!=0)										//Проверка, было ли дерево верным
	{
		cout << "Введено неверное дерево." << endl;
		return 0;
	}
	cout << endl << "Создан вектор бинарного дерева" << endl;
	char str_tree[100000];
	cout<<"Полученное дерево наглядно выглядит как :"<<endl;
	visuale(tree,str_tree);
	cout<<str_tree<<endl;
	char str[100];
	str[0]='\0';
	klp(tree,str,0,0);									//Создание КЛП
	cout << "КЛП введенного дерева:"<<endl;
	cout<<str<<endl;
	tree->clear();										//Отчистка вектора
	free(tree);										//Высвобождение памяти
}
