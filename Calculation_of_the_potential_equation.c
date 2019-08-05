#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_Queue_Size 100

struct Queuetype {
	int queue[Max_Queue_Size];
	int front, rear;
};
typedef struct Queuetype Queuetype;

void init(Queuetype *q)
{
	q->rear = q->front = 0;
}
int is_empty(Queuetype *q)
{
	return (q->front == q->rear);
}
int is_full(Queuetype *q)
{
	return (q->rear == (Max_Queue_Size - 1));
}
void enqueue(Queuetype *q, int item)
{
	if (is_full(q))
		return;
	else
	{
		q->rear = (q->rear + 1) % Max_Queue_Size;
		q->queue[q->rear] = item;
	}
}
int dequeue(Queuetype *q)
{
	if (is_empty(q))
		exit(0);
	q->front = (q->front + 1) % Max_Queue_Size;
	return q->queue[q->front];
}
int comp(int a)
{
	if (a != '+'&&a != '-'&&a != '*'&&a != '/')
		return 1;
	else
		return 0;
}
void calculate(Queuetype *q, char *str)
{
	int i;
	int n = strlen(str);
	int ch1, ch2, ch3, data;

	for (i = 0; i<n; i++)
	{
		if (i < n - 2)
		{
			ch1 = str[i];
			ch2 = str[i + 1];
			ch3 = str[i + 2];
		}
		else
			ch1 = ch2 = ch3 = str[i];
		if (comp(ch1) == 0 && comp(ch2) == 1 && comp(ch3) == 1)
		{
			ch2 = ch2 - '0';
			ch3 = ch3 - '0';
			switch (ch1)
			{
			case '+':
				data = ch2 + ch3;
				enqueue(q, data);
				break;
			case '-':
				data = ch2 - ch3;
				enqueue(q, data);
				break;
			case '*':
				data = ch2 * ch3;
				enqueue(q, data);
				break;
			case '/':
				data = ch2 / ch3;
				enqueue(q, data);
				break;
			}
			i += 2;
		}
		else
		{
			if (comp(ch1) == 0)
				enqueue(q, ch1);
			else
			{
				data = ch1 - '0';
				enqueue(q, data);
			}
		}
	}
	ch1 = dequeue(q);
	ch2 = dequeue(q);
	ch3 = dequeue(q);
	while ((q->front + 1) % Max_Queue_Size != q->rear)
	{
		if (comp(ch1) == 0 && comp(ch2) == 1 && comp(ch3) == 1)
		{
			switch (ch1)
			{
			case '+':
				data = ch2 + ch3;
				enqueue(q, data);
				break;
			case '-':
				data = ch2 - ch3;
				enqueue(q, data);
				break;
			case '*':
				data = ch2 * ch3;
				enqueue(q, data);
				break;
			case '/':
				data = ch2 / ch3;
				enqueue(q, data);
				break;
			}
			if ((q->front + 1) % Max_Queue_Size != q->rear)
			{
				ch1 = dequeue(q);
				ch2 = dequeue(q);
				ch3 = dequeue(q);
			}
		}
		else
		{
			enqueue(q, ch1);
			ch1 = ch2;
			ch2 = ch3;
			ch3 = dequeue(q);
		}

	}

	printf("전위식 : %s\n", str);
	printf("결과 : %d\n", dequeue(q));
}

int main(void)
{
	Queuetype q;

	init(&q);
	calculate(&q, "-+*9+28*+4863");

	return 0;
}