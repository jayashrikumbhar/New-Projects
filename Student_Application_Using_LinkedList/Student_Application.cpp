/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Student Application Using Linked List
//	1. Enquiry Form of Student
//	2. Sort first 15 student based on merit list from given enquiry of stundent
//	3. After adding student from enquiry then remove that record from enquiry and add it into non admitted student list
//	4. Display information of second rank student
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<malloc.h>

#define TRUE 1
#define FALSE 0

typedef unsigned int BOOL;

typedef struct Student
{
	int Std_Id;
	char Name[50];
	char Mob_No[11];
	float Percentage;
	struct Student *Next;
}STUD,*PSTUD,**PPSTUD;

static int E_ID = 1;						//Student id for enquiry
static int Std_ID = 1;						//Student Id when student admitted
static float Max_Marks = 0.0;				//To keep maximum marks of student

//////////////////Declarations//////////////////////
BOOL Enquiry_Student(PSTUD);
void Search_Max_Merit(PSTUD);
void Admit_Student(PPSTUD,PPSTUD,PPSTUD);
//void Remove_Stud_From_Enquiry(PPSTUD,PPSTUD);
void Display_Student(PSTUD);


//////////////////////////////////////////////////////////////////////////
//	Function Name : Enquiry_Student
//	Input : PSTUD
//	Output : Integer
//	Author : J.A.Kumbhar
//	Date : 08/07/2020
//////////////////////////////////////////////////////////////////////////

BOOL Enquiry_Student(PPSTUD First)
{
		char ch;
		int iCnt = 0;
		PSTUD NewStud = NULL;
		PSTUD Temp = *First;

		NewStud = (PSTUD)malloc(sizeof(STUD));

		if(NewStud == NULL)
		{
			return FALSE;					//if memory for new student is not allocate then it return -1 as failure
		}
		fflush(stdin);
		NewStud -> Std_Id = E_ID;
		printf("Enter Student Name:\n");
		scanf("%[^\n]s",&NewStud->Name);
		printf("Enter Mobile Number:\n");
		while(iCnt < 10)
		{
				ch = getche();
				if((ch >= '0') && (ch <= '9'))
				{
						NewStud ->Mob_No[iCnt++] = ch;
				}
				else
				{
					printf("\b");
				}
		}
		getch();
		printf("\nEnter Percentage of student:\n");
		scanf("%f",&NewStud->Percentage);
		NewStud->Next = NULL;

		if(*First == NULL)
		{
			Temp = *First = NewStud;
			E_ID++;
			return TRUE;					//When Successfully add student in enquiry
		}
		else
		{
			while(Temp -> Next != NULL)
			{
				Temp = Temp -> Next;
			}

			Temp -> Next = NewStud;
			Temp = Temp -> Next;

			E_ID++;
			return TRUE;
		}
}

//////////////////////////////////////////////////////////////////////////
//	Function Name : Search_Max_Merit
//	Input : PSTUD
//	Output : Integer
//	Author : J.A.Kumbhar
//	Date : 08/07/2020
//////////////////////////////////////////////////////////////////////////

void Search_Max_Merit(PSTUD First)
{
	Max_Marks = First->Percentage;
	First = First->Next;

	while(First != NULL)
	{
		if(First -> Percentage > Max_Marks)
		{
			Max_Marks = First->Percentage;
		}
		First = First -> Next;
	}
}

//////////////////////////////////////////////////////////////////////////
//	Function Name : Admit_Student
//	Input : PSTUD
//	Output : Integer
//	Author : J.A.Kumbhar
//	Date : 08/07/2020
//////////////////////////////////////////////////////////////////////////

void Admit_Student(PPSTUD First,PPSTUD Add,PPSTUD NAStud)
{
		Search_Max_Merit(*First);
		PSTUD Temp = *First;
		PSTUD Temp1 = NULL;
		
		while(Temp != NULL)
		{
			if(Temp->Percentage == Max_Marks)
			{
				break;
			}
			Temp1 = Temp;
			Temp = Temp -> Next;
		}

		if(*First == Temp)				//if 1st student has maximum marks 
		{
			*First = Temp -> Next;		//Store address of 2nd student after removing 1st student
			Temp -> Next = NULL;		//if not set null then all student are added
		}
		else
		{
			Temp1 -> Next = Temp -> Next;
			Temp -> Next = NULL;
		}

		if(Temp != NULL)
		{
			if(*Add == NULL)
			{
				*Add = Temp;
			}
			else
			{
				Temp->Next = *Add;
				*Add = Temp;
			}
			Std_ID++;
		}

		//After admission we have to remove that student from enquiry list
		//Remove_Stud_From_Enquiry(&First,NAStud);

}

//////////////////////////////////////////////////////////////////////////
//	Function Name : Remove_Stud_From_Enquiry
//	Input : PPSTUD,PPSTUD
//	Output : Integer
//	Author : J.A.Kumbhar
//	Date : 08/07/2020
//////////////////////////////////////////////////////////////////////////

//void Remove_Stud_From_Enquiry(PPSTUD First,PPSTUD NAStud)
//{
//		PSTUD Temp1,Temp2;
//		Temp1 = *First;
//		Temp2 = NULL;
//		PSTUD NewStud = NULL;
//
//		NewStud = (PSTUD)malloc(sizeof(STUD));
//
//		if(NewStud == NULL)
//		{
//			return;					//if memory for new student is not allocate then it return -1 as failure
//		}
//
//		while(Temp1 != NULL)
//		{
//			if(Temp1->Percentage == Max_Marks)
//			{
//				break;
//			}
//			Temp2 = Temp1;
//			Temp1 = Temp1 -> Next;
//		}
//
//		NewStud -> Std_Id = Std_ID;
//		strcpy(NewStud -> Name,Temp1 -> Name);
//		strcpy(NewStud -> Mob_No, Temp1 -> Mob_No);
//		NewStud -> Percentage = Temp1 -> Percentage;
//		NewStud -> Next = NULL;
//
//		if(Temp1 != NULL)
//		{
//			Temp2 -> Next = Temp1 -> Next;
//			free(Temp1);
//
//			if(*NAStud == NULL)
//			{
//				*NAStud = NewStud;
//			}
//			else
//			{
//				Temp1 = *NAStud;
//
//				while(Temp1->Next != NULL)
//				{
//					Temp1 = Temp1->Next;
//				}
//
//				Temp1->Next = NewStud;
//			}
//		}
//
//}


//////////////////////////////////////////////////////////////////////////
//	Function Name : Display_Student
//	Input : PSTUD
//	Output : Integer
//	Author : J.A.Kumbhar
//	Date : 08/07/2020
//////////////////////////////////////////////////////////////////////////

void Display_Student(PSTUD First)
{
	if(First == NULL)
	{
		printf("No Student is Added!!\n");
	}

	else
	{
		while(First != NULL)
		{
			printf("=================== STUDENT DETAILS ======================\n\n");
			printf("Student ID => %d\n\n",First->Std_Id);
			printf("Student Name => %s\n\n",First->Name);
			printf("Student Mobile No. => %s\n\n",First->Mob_No);
			printf("Student Percentage => %f\n\n",First->Percentage);
			printf("==========================================================\n\n");

			First = First -> Next;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//	Function Name : main
//	Input : None
//	Output : Integer
//	Author : J.A.Kumbhar
//	Date : 08/07/2020
//////////////////////////////////////////////////////////////////////////

int main()
{
	PSTUD Head = NULL;
	PSTUD Add = NULL;
	PSTUD NAStud = NULL;
	BOOL bRet = FALSE;
	int i = 0,choice = 0;

	/*Remove_Stud_From_Enquiry(&Head,&NAStud);*/

	while(1)
	{
		menu:
		
		printf("============= Welcome To Fork Infosystems ==============\n\n");
		printf("**********************************************************************************************\n\n");
		printf("*\t1. Enquiry\n\n*\t2. Add Student\n\n*\t3. Display Admitted Student\n\n*\t4. Display Students Enquiry\n\n*\t5. Display Non Admitted student\n\n");
		printf("**********************************************************************************************\n\n");

		printf("Enter the Choice:\n");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:
				bRet = Enquiry_Student(&Head);
				if(bRet == TRUE)
				{
					printf("Record Added Successfully!!!\n");
				}
				else
				{
					printf("Unable to add Record!!\n");
				}
				break;

			case 2:
				Admit_Student(&Head,&Add,&NAStud);
				break;

			case 3:
				Display_Student(Add);
				break;

			case 4:
				Display_Student(Head);
				break;

			case 5:
				Display_Student(Head);
				break;

			default:
				printf("Invalid choice!!");
				goto menu;
				break;

		}
	}
	
	

	getch();
	return 0;
}


