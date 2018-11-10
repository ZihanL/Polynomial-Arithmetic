//============================================================================
// Name        : PolynomialArithmetic.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;

//建立多项式的项
struct term
{
	double coefficient;
	int exponent;
	struct term *next;//指向的下一个节点是一个结构体
};
typedef struct term terms;

/*
description: create a polynomial
parameter: void
return: struct term
*/
terms * createp();


terms * clone(terms * head, double a);
/*
description: create a polynomial
parameter: void
return: struct term
*/
void output(terms *head);

/*
description: sort a polynomial
parameter: struct term
return: void
*/
void sort(terms *head);

void menu(void);





/*
description: adding two polynomials together
parameter: the first and the second polynomial
return: the result polynomial
*/
terms * add(terms * head, terms * second);

/*
description: subtract two polynomials together
parameter: the first and the second polynomial
return: the result polynomial
*/
terms *subtract(terms * head, terms * second);

/*
description: multiply two polynomials together
parameter:the first and the second polynomial
return: the result polynomial
*/
terms *multiply(terms * head, terms * second);

/*
description: divide two polynomials together
parameter:the first and the second polynomial
return: the result polynomial
*/
terms **division(terms * head, terms * second);

terms * clearzero(terms * head);

void divisionpart(terms * dividend, terms * divisor, terms * interm);








int main(void)
{
	menu();
}

void menu(void)
{
	int a = 0;

	cout << "Please choose the function you want to do: " << endl;
	cout << "If you want to create the polynomials, please input '1'." << endl;
	cout << "If you want to add the polynomials, please input '2'." << endl;
	cout << "If you want to minus the polynomials, please input '3'." << endl;
	cout << "If you want to multiple the polynomials, please input '4'." << endl;
	cout << "If you want to sort the polynomials, please input '5'." << endl;
	cout << "If you want to exit, please input '6'." << endl;
	cout << "Please input your number: ";
	terms * m = NULL;
	terms * n = NULL;


	while(true)
	{

		cin >> a;
		switch(a)
		{
			case 1:
				{
					m = createp();
					cout << "The first polynomial is: ";
					output(m);
					n = createp();
					cout << "The second polynomial is: ";
					output(n);
					break;
				}
			case 2:
				{

					if(m == NULL)
					{
						cout << "Please create two polynomial before adding. " << endl;
					}
					else
					{

					    terms * sum = add(m, n);

						cout << "The result is: ";
						output(sum);

					}
					break;
				}

			case 3:
				{

					if(m == NULL)
					{
						cout << "Please create two polynomial before subtracting. " << endl;
					}
					else
					{

					    terms * minus = subtract(m, n);

						cout << "The result is: ";
						output(minus);

					}
					break;
				}
			case 4:
					{

					if(m == NULL)
					{
						cout << "Please create two polynomials before multiplying. " << endl;
					}
					else
					{

					    terms * product = multiply(m, n);
						cout << "The result is: ";
						output(product);

					}
					break;
				}
			case 5:
				{
					if(m == NULL)
					{
						cout << "Please create two polynomials before sorting. " << endl;

					}
					else
					{
				        cout << "This is the current polynomials: " << endl;
				        cout << "FIRST: ";
				        output(m);
				        cout << endl;
				        cout << "SECOND: ";
				        output(n);
				        cout << endl;
						sort(m);
						sort(n);

						cout << "After sorting it looks like this: " << endl;
						cout << "FIRST: ";
				        output(m);
				        cout << endl;
				        cout << "SECOND: ";
				        output(n);
				        cout << endl;

					}
					break;
				}

			case 6:
				{
					cout << "            =============================" << endl;
					cout << "            Thanks for using this program" << endl;
					cout << "                        BYE BYE          " << endl;
					cout << "            =============================" << endl;
 					exit(0);

				}
		}
	}


}



terms * clearzero(terms * head)
{

	terms * pa = head;
	terms * pb = NULL;
	terms * pc = NULL;
	//delete the term with a '0' coefficient
	while(pa != NULL)
	{

		if(pa->coefficient == 0)
		{
			if(pb == NULL)
			{
				pb = pa->next;
				delete pa;

				head = pb;
				pa = pb;
			}
			else
			{
				pb->next = pa->next;
				delete pa;
				pa = pb->next;
			}


		}
		else
		{
			pb = pa;
			pa = pa->next;
		}

	}


	pa = head;
	pb = pa;

	//combine the terms with the same coefficient
	while(pa != NULL)
	{
		pb = pa->next;
		pc = pa;
		while(pb != NULL)
		{
			if(pb->exponent == pa->exponent)
			{
				pa->coefficient += pb->coefficient;
			    pc->next = pb->next;
			    delete pb;
			    pb = pc->next;
			}
			else
			{
				pc = pb;
				pb = pb->next;

			}
		}
		pa = pa->next;
	}
	return head;
}




terms * createp()
{
	int exponent = 0;
	double coefficient = 0;
    terms * head = NULL;
	terms *p = head;

	cout << "Please input the coefficient and then the exponent of the term," << endl;
	cout << "it will stop when you input '0' for the coefficient." << endl;
	cin >> coefficient;
	cin >> exponent;
	cout << "; " << endl;
	if(coefficient != 0 || exponent != 0 )
	{
		head = new terms;
		head->exponent = exponent;
		head->coefficient = coefficient;
		head->next = NULL;
		p = head;
	}
	else
	{
		return head;
	}

	int flag = 0;
	do
	{
		cin >> coefficient;
		cin >> exponent;
		cout << "; " << endl;
		if(exponent >= 0 && coefficient != 0)
		{

			terms * linkterm = new terms;
			linkterm->coefficient = coefficient;
			linkterm->exponent = exponent;
			linkterm->next = NULL;
			p->next = linkterm;
			p = linkterm;

		}
	    if(coefficient == 0 && exponent == 0 )
	    {
	    	break;
		}

	}while(true);



	if(flag == 0)
	{
		return head;
	}
	else
	{
		cout << "The exponent can not be a minus number, this is not a polynomial, please input again." << endl;
	}


}

terms * clone(terms * head, double a)
{
	terms * first = head;
	terms * c = new terms;
	c->coefficient = 0;
	c->exponent = -1;
	terms * p = c;

	while(first != NULL)
	{
		terms * link = new terms;
		link->coefficient = a * first->coefficient;
		link->exponent = first->exponent;
		link->next = NULL;
		p->next = link;
		p = link;

		first = first->next;
	}

	return c->next;
}



void output(terms *head)
{
	terms *p = head;
	while( p != NULL)
	{
		cout << "("<< p->coefficient << "x^" << p->exponent << ")";

		if(p->next != NULL)
		{
			cout << " + ";
		}
		else
		{
			cout << endl;
		}
		p = p->next;
	}
}

void sort(terms *head)
{
	head = clearzero(head);
	terms * pi = NULL;
	terms * pk = NULL;
	terms * pj = NULL;
	int a = 0;
	double b = 0;
	for(pi = head->next; pi->next != NULL; pi = pi->next)
	{

		pk = pi;
		for(pj = pi->next; pj != NULL; pj = pj->next)
		{
			if(pj->exponent > pk->exponent)
			{
				pk = pj;
			}

		}
		if(pk != pi)
		{
			a = pk->exponent;
			pk->exponent = pi->exponent;
			pi->exponent = a;

			b = pk->coefficient;
			pk->coefficient = pi->coefficient;
			pi->coefficient = b;



		}
	}
}

terms * add(terms * head, terms * second)
{
	terms * sum = clone(head, 1);

	terms * result = sum;
	terms * first = head;
	terms * two = second;

	while(two != NULL)
	{
			first = head;
			result = sum;

			int flag = 0;
			while(first != NULL)
			{
				if(two->exponent == first->exponent)
				{

					flag = 1;
					result->coefficient = first->coefficient + two->coefficient;

				}


				result = result->next;
				first = first->next;
			}



			if(flag == 0)
			{

				terms * s = new terms;
				s->coefficient = two->coefficient;
				s->exponent = two->exponent;
				s->next = NULL;
				s->next = sum->next;
				sum->next = s;


			}
			two = two->next;

	}

			return sum;
}

terms *subtract(terms * head, terms * second)
{
		terms * a = clone(second, -1);
		terms * minus = add(head, a);
		return minus;
}



terms * multiply(terms * head, terms * second)
{
	terms * r = new terms;
	r->coefficient = 0;
	r->exponent = -1;
	terms * p = r;
	terms * first = head;
	terms * two = second;

	while(first != NULL)
	{
		two = second;
		while(two != NULL)
		{
			terms * link = new terms;
			link->coefficient = first->coefficient * two->coefficient;
			link->exponent = first->exponent + two->exponent;
			link->next = NULL;
			p->next = link;
			p = link;


			two = two->next;

		}

		first = first->next;
	}
	r->next = clearzero(r->next);

	return r->next;
}

terms **division(terms * head, terms * second)
{
	terms * divide [2] =  {NULL, NULL};
	terms * one = head;
	terms * two = second;
	terms * quotient = new terms;
	quotient->coefficient = 0;
	quotient->exponent = -1;
	quotient->next = NULL;
	terms * remainder = new terms;
	remainder->coefficient = 0;
	remainder->exponent = -1;
	remainder->next = NULL;

	terms * p = quotient;

	if(one->exponent < two->exponent)
	{
		terms * pa = new terms;
		pa->coefficient = 0;
		pa->exponent = 0;
		quotient->next = pa;
		divide[0] = quotient;

		remainder->next = one;
		divide[1] = remainder;
		return  divide;
	}

	int a = 0;
	terms * s = clone(head, 1);


	do
	{
			terms * link = new terms;
			link->coefficient = s->coefficient / two->coefficient;
			link->exponent = s->exponent - two->exponent;
			a = link->exponent;
			link->next = NULL;
			p->next = link;
			p = link;

			terms * b = multiply(link, two);
			s = subtract(s,b);

			s = clearzero(s);


			output(b);
			output(s);
			break;



	}while(a != 0);

	remainder = s;
	divide[0] = quotient;
	divide[1] = remainder;

	return divide;

}





