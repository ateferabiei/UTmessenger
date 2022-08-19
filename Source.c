#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Header.h"

int main() {
	struct person *head ;
	head = (struct person*)malloc(sizeof(struct person));
	head->username = (char *)malloc(10 * sizeof(char));
	head->password = (char *)malloc(10 * sizeof(char));
	head->phonenumber = (char *)malloc(14 * sizeof(char));
	strcpy(head->username, "username:");
	strcpy(head->password, "password:");
	strcpy(head->phonenumber, "phonenumber:");
	head->next = NULL;
	struct sent_message *head1 ;
	head1 = (struct sent_message*)malloc(sizeof(struct sent_message));
	head1->message = (char *)malloc(8 * sizeof(char));
	head1->rec_user = (char *)malloc(10 * sizeof(char));
	head1->sen_user = (char *)malloc(11 * sizeof(char));
	head1->time_message = (char *)malloc(6 * sizeof(char));
	strcpy(head1->rec_user, "send_for:");
	strcpy(head1->sen_user, "send_from:");
	strcpy(head1->message, "message:");
	strcpy(head1->time_message, "time:");
	head1->next = NULL;
	struct received_message *head2;
	head2 = (struct received_message*)malloc(sizeof(struct received_message));
	head2->message = (char *)malloc(8 * sizeof(char));
	head2->rec_message = (char *)malloc(10 * sizeof(char));
	head2->sen_message = (char *)malloc(11 * sizeof(char));
	head2->time_message = (char *)malloc(6 * sizeof(char));
	strcpy(head2->message, "message:");
	strcpy(head2->rec_message, "send_for:");
	strcpy(head2->sen_message, "send_from");
	strcpy(head2->time_message, "time:");
	head2->A = 1;
	head2->next = NULL;
	read_from_file(head, head1, head2);
	printf("welcome to UTMESSAGER\n");
	while (1) {
		char *check_user;
		check_user = (char *)malloc(sizeof(char));
		check_user = '\0';
		char *check_phonenumber;
		check_phonenumber= (char *)malloc(sizeof(char));
		check_phonenumber = '\0';
		char *command;
		command = (char *)malloc(sizeof(char));
		command = '\0';
		char *check_pass;
		check_pass = (char *)malloc(sizeof(char));
		check_pass = '\0';
		int i=0;
		char c;
		char *c1;
		c1 = (char *)malloc(sizeof(char));
		printf(">>");
		while (1) {
			c = getchar();
			c1[i] = c;
			i++;
			c1 = (char *)realloc(c1,(i+1)* sizeof(char));
			if (c == ' ' || c == '\n') {
				c1[i-1] = '\0';
				if (command == '\0') {
					command = (char *)realloc(command, i * sizeof(char));
					strcpy(command, c1);
				}
				else if (check_user == '\0') {
					check_user = (char *)realloc(check_user, i * sizeof(char));
					strcpy(check_user, c1);
				}
				else if (check_pass == '\0') {
					check_pass = (char *)realloc(check_pass, i * sizeof(char));
					strcpy(check_pass, c1);
				}
				else if (check_phonenumber == '\0') {
					check_phonenumber = (char *)realloc(check_phonenumber, i * sizeof(char));
					strcpy(check_phonenumber, c1);
				}
				if (c == '\n') {
					free(c1);
					c1 = (char *)malloc(sizeof(char));
					i = 0;
					break;
				}
				else {
					free(c1);
					c1 = (char *)malloc(sizeof(char));
					i = 0;
					continue;
				}
			}
		}
			if (strcmp(command, "signup") == 0) {
				if (signup(check_user, check_pass, check_phonenumber, head)) {
					printf("\nit is Successful\n");
					if (start_UTMESSAGER(head, check_user, head1, head2) == 1) {
						write_in_file(head, head1, head2, check_user);
						break;
					}
					else
						continue;
				}
				else
					continue;
			}
			else if (strcmp(command, "login") == 0) {
				if (login(check_user, check_pass, head)) {
					printf("\nit is Successful\n");
					if (start_UTMESSAGER(head, check_user, head1, head2) == 1) {
						write_in_file(head, head1, head2, check_user);
						break;
					}
					else
						continue;
				}
				else
					continue;
			}
			else if (strcmp(command, "close") == 0) {
				printf("\nit is Successful\n");
				write_in_file(head, head1, head2, check_user);
				break;
			}
			else {
				printf("\nthis command is not available\n");
				continue;
			}
		
	}
}
void read_from_file(struct person *head, struct sent_message *head1, struct received_message *head2) {
	FILE *read_file = fopen("data.csv", "r");
	if (read_file != NULL) {
		char ch ;
		long int i = 0;
		char *filecontent;
		filecontent = (char *)malloc( sizeof(char));
		while (!feof(read_file)) {
			ch = getc(read_file);
			filecontent[i] = ch;
			i++;
			filecontent = (char *)realloc(filecontent,(i + 1) * sizeof(char));
		}
		fclose(read_file);
		write_in_struct( head, head1, head2,filecontent );
	}
}
void write_in_struct(struct person *head, struct sent_message *head1, struct received_message *head2, char *filecontent) {
	struct person *check16;
	check16 = (struct person*)malloc(sizeof(struct person));
	struct sent_message *check_message8;
	check_message8 = (struct sent_message*)malloc(sizeof(struct sent_message));
	struct received_message *check_message9;
	check_message9 = (struct received_message*)malloc(sizeof(struct received_message));
	check16 = head;
	check_message8 = head1;
	check_message9 = head2;
	char *p;
	char p1;
	p = (char *)malloc(sizeof(char));
	int i = 0,k=0;
	while (1) {
		p = (char *)realloc(p, (i + 1) * sizeof(char));
		p1 = filecontent[k];
		p[i]=p1;
		i++;
		k++;
		if (p1 == ',' || p1 == '\n') {
			if (p1 == '\n') {
				free(p);
				i = 0;
				p = (char *)malloc(sizeof(char));
				break;
			}
			p[i-1] = '\0';
			while (check16->next != NULL ) {
				if (check16->next->username == '\0' || check16->next->password == '\0' || check16->next->phonenumber == '\0')
					break;
				check16 = check16->next;
			}
			if (check16->next == NULL) {
				check16->next = (struct person *)malloc(sizeof(struct person));
				check16->next->next = NULL;
				check16->next->password = (char *)malloc(sizeof(char));
				check16->next->username = (char *)malloc(sizeof(char));
				check16->next->phonenumber = (char *)malloc(sizeof(char));
				check16->next->password = '\0';
				check16->next->phonenumber = '\0';
				check16->next->username = '\0';
			}
			if (check16->next->username == '\0') {
				check16->next->username = (char *)realloc(check16->next->username, (strlen(p)) * sizeof(char));
				strcpy(check16->next->username, p);
			}
			else if (check16->next->password == '\0') {
				check16->next->password = (char *)realloc(check16->next->password, (strlen(p)) * sizeof(char));
				strcpy(check16->next->password, p);
			}
			else {
				check16->next->phonenumber = (char *)realloc(check16->next->phonenumber, (strlen(p)) * sizeof(char));
				strcpy(check16->next->phonenumber, p);
			}
			i = 0;
			free(p);
			p = (char *)malloc(sizeof(char));
		}
	}
	while (1) {
		p = (char *)realloc(p, (i + 1) * sizeof(char));
		p1 = filecontent[k];
		p[i] = p1;
		i++;
		k++;
		if (p1 == ',' || p1 == '\n') {
			if (p1 == '\n') {
				free(p);
				i = 0;
				p = (char *)malloc(sizeof(char));
				break;
			}
			p[i - 1] = '\0';
			while (check_message8->next != NULL) {
				if (check_message8->next->message == '\0' || check_message8->next->rec_user == '\0' || check_message8->next->sen_user == '\0')
					break;
				check_message8 = check_message8->next;
			}
			if (check_message8->next == NULL) {
				check_message8->next = (struct sent_message *)malloc(sizeof(struct sent_message));
				check_message8->next->next = NULL;
				check_message8->next->message = (char *)malloc(sizeof(char));
				check_message8->next->rec_user = (char *)malloc(sizeof(char));
				check_message8->next->sen_user = (char *)malloc(sizeof(char));
				check_message8->next->time_message = (char *)malloc(sizeof(char));
				check_message8->next->message = '\0';
				check_message8->next->rec_user = '\0';
				check_message8->next->sen_user = '\0';
				check_message8->next->time_message = '\0';
			}
			if (check_message8->next->message == '\0') {
				check_message8->next->message = (char *)realloc(check_message8->next->message, (strlen(p)) * sizeof(char));
				strcpy(check_message8->next->message, p);
			}
			else if (check_message8->next->rec_user == '\0') {
				check_message8->next->rec_user = (char *)realloc(check_message8->next->rec_user, (strlen(p)) * sizeof(char));
				strcpy(check_message8->next->rec_user, p);
			}
			else if(check_message8->next->sen_user=='\0') {
				check_message8->next->sen_user = (char *)realloc(check_message8->next->sen_user, (strlen(p)) * sizeof(char));
				strcpy(check_message8->next->sen_user, p);
			}
			i = 0;
			free(p);
			p = (char *)malloc(sizeof(char));
		}
	}
	while (1) {
		p = (char *)realloc(p, (i + 1) * sizeof(char));
		p1 = filecontent[k];
		p[i] = p1;
		i++;
		k++;
		if (p1 == ',' || p1 == '\n') {
			if (p1 == '\n') {
				free(p);
				i = 0;
				p = (char *)malloc(sizeof(char));
				break;
			}
			p[i - 1] = '\0';
			while (check_message9->next != NULL) {
				if (check_message9->next->message == '\0' || check_message9->next->rec_message == '\0' || check_message9->next->sen_message == '\0')
					break;
				check_message9 = check_message9->next;
			}
			if (check_message9->next == NULL) {
				check_message9->next = (struct received_message *)malloc(sizeof(struct received_message));
				check_message9->next->next = NULL;
				check_message9->next->message = (char *)malloc(sizeof(char));
				check_message9->next->rec_message = (char *)malloc(sizeof(char));
				check_message9->next->sen_message = (char *)malloc(sizeof(char));
				check_message9->next->time_message = (char *)malloc(sizeof(char));
				check_message9->next->message = '\0';
				check_message9->next->rec_message = '\0';
				check_message9->next->sen_message = '\0';
				check_message9->next->time_message = '\0';
			}
			if (check_message9->next->message == '\0') {
				check_message9->next->message = (char *)realloc(check_message9->next->message, (strlen(p)) * sizeof(char));
				strcpy(check_message9->next->message, p);
			}
			else if (check_message9->next->rec_message == '\0') {
				check_message9->next->rec_message = (char *)realloc(check_message9->next->rec_message, (strlen(p)) * sizeof(char));
				strcpy(check_message9->next->rec_message, p);
			}
			else if (check_message9->next->sen_message=='\0'){
				check_message9->next->sen_message = (char *)realloc(check_message9->next->sen_message, (strlen(p)) * sizeof(char));
				strcpy(check_message9->next->sen_message, p);
			}
			i = 0;
			free(p);
			p = (char *)malloc(sizeof(char));
		}
	}
}
int signup(char *check_user, char *check_pass, char *check_phonenumber, struct person *head) {
	struct person *check1;
	check1 = (struct person*)malloc(sizeof(struct person));
	int a1=0, a2=0,  a3=0, a4=0;
	check1= head;

		while (check1->next != NULL) {
			if (strcmp(check1->next->phonenumber , check_phonenumber)==0) {
				a4++;
			}
			if (strcmp(check1->next->username , check_user)==0) {
				a1++;
			}
			check1 = check1->next;
		}
	
	if (a1 == 0)
		a1 = 1;
	else
		a1 = 0;
	if (a4 == 0)
		a4 = 1;
	else
		a4 = 0;
	check1->next = (struct person*)malloc(sizeof(struct person));
	check1->next->next = NULL;
	check1->next->username = (char *)malloc((strlen(check_user)) * sizeof(char));
	check1->next->password= (char *)malloc((strlen(check_pass)) * sizeof(char));
	check1->next->phonenumber=(char *)malloc((strlen(check_phonenumber)) * sizeof(char));
	strcpy(check1->next->username, check_user);
	a2 = check_size_password(check_pass);
	strcpy(check1->next->password, check_pass);
	a3 = check_phonenumber_size(check_phonenumber);
	strcpy(check1->next->phonenumber, check_phonenumber);
	if (a1 == 1 && a2 == 1 && a3 == 1 && a4 == 1)
		return 1;
	else {
		printf("\nit is wrong please type your command again\n");
		return 0;
	}
}
int check_size_password(char *check_pass) {
	if (strlen(check_pass) > 5)
		return 1;
	else
		return 0;
}
int check_phonenumber_size(char *check_phonenumber) {
	int k=0;
	if (strlen(check_phonenumber) == 11) {
		for (int i = 0; i != 11; i++) {
			if (check_phonenumber[i] == '1' || check_phonenumber[i] == '2' || check_phonenumber[i] == '3' || check_phonenumber[i] == '4' || check_phonenumber[i] == '6' || check_phonenumber[i] == '7' || check_phonenumber[i] == '8' || check_phonenumber[i] == '9' || check_phonenumber[i] == '0'|| check_phonenumber[i] == '5')
				k++;
		}
		if (k == 11) {
			if (check_phonenumber[0] == '0')
				return 1;
			else
				return 0;
		}
		else
			printf("your number is wrong");
	}
	else
		return 0;
}
int login(char *check_user,char *check_pass,struct person *head) {
	int b1=0,b2=0;
	struct person *check3;
	check3 = (struct person*)malloc(sizeof(struct person));
	check3= head;
	while (check3!=NULL ) {
		if (strcmp(check3->username, check_user)==0) {
			b1 = 1;
			break;
		}
		check3= check3->next;
	}
	if (check3 == NULL) {
		printf("it is not there\n");
		return 0;
	}
	if (strcmp(check3->password, check_pass) == 0)
		b2=1;
	else {
		b2 = 0;
	}
	if (b1 == 1 && b2 == 1)
		return 1;
	else {
		printf("\nit is not there\n");
		return 0;
	}
}
int start_UTMESSAGER(struct person *head,char *check_user, struct sent_message *head1, struct received_message *head2) {
	char  *user1, *message1;
	char *command1;
	command1 = (char *)malloc(sizeof(char));
	user1 = (char *)malloc( sizeof(char));
	message1 = (char *)malloc( sizeof(char));
	show_unread_message(head2, check_user);
	char ch;
	char *ch1;
	ch1 = (char *)malloc(sizeof(char));
	int i1=0;
	while (1) {
		command1 = '\0';
		user1 = '\0';
		message1 = '\0';
		printf(">>");
		while (1) {
			ch = getchar();
			ch1[i1] = ch;
			i1++;
			ch1 = (char *)realloc(ch1, (i1 + 1) * sizeof(char));
			if (ch == ' ' || ch == '\n') {
				ch1[i1-1] = '\0';
				if (command1 == '\0') {
					command1 = (char *)realloc(command1, i1 * sizeof(char));
					strcpy(command1, ch1);
				}
				else if (user1 == '\0') {
					user1 = (char *)realloc(user1, i1 * sizeof(char));
					strcpy(user1, ch1);
				}
				else {
					message1 = (char *)realloc(message1, i1 * sizeof(char));
					strcpy(message1, ch1);
				}
				if (ch == '\n') {
					free(ch1);
					ch1 = (char *)malloc(sizeof(char));
					i1 = 0;
					break;
				}
				else {
					free(ch1);
					ch1 = (char *)malloc(sizeof(char));
					i1 = 0;
					continue;
				}
			}
		}
		if (strcmp(command1, "logout") == 0) {
			return 0;
			break;
		}
		else if (strcmp(command1, "send") == 0) {
			send_message(head,check_user,user1,head1,head2, message1);
			continue;
		}
		else if (strcmp(command1, "show_sent") == 0) {
			show_sent_message(check_user,head1,user1);
			continue;
		}
		else if (strcmp(command1, "show_received") == 0) {
			show_received_message(check_user,head2,user1);
			continue;
		}
		else if (strcmp(command1, "info") == 0) {
			show_info(head);
			continue;
		}
		else if (strcmp(command1, "about") == 0) {
			show_about(head, user1);
			continue;
		}
		else if (strcmp(command1, "close") == 0) {
			return 1;
			break;
		}
		else if (strcmp(command1, "edit_username") == 0) {
			edit_username(check_user, user1, head);
			continue;
		}
		else if (strcmp(command1, "edit_password") == 0) {
			edit_password(check_user, user1, head);
		}
		else {
			printf("the command is not available\n");
			continue;
		}
	}
}
void show_unread_message(struct received_message *head2, char *check_user) {
	struct received_message *check_message5;
	check_message5 = (struct received_message*)malloc(sizeof(struct received_message));
	check_message5 = head2;
	while (check_message5 != NULL) {
		if (strcmp(check_message5->rec_message, check_user) == 0) {
			if (check_message5->A==0) {
			printf("\n%s\n%s\n", check_message5->message, check_message5->sen_message);
			if (check_message5->time_message != NULL)
				printf("%s\n", check_message5->time_message);
			check_message5->A = 1;
		}
		}
		check_message5 = check_message5->next;
	}
}
void send_message(struct person *head, char *check_user, char *user1, struct sent_message *head1, struct received_message *head2, char *message1) {
	struct person *check9, *check11;
	int d1 = 0, d2 = 0;
	check9 = (struct person*)malloc(sizeof(struct person));
	check9 = head;
	while (check9 != NULL) {
		if (strcmp(user1, check9->username) == 0) {
			d1 = 1;
			break;
		}
		check9 = check9->next;
	}
	check11 = (struct person*)malloc(sizeof(struct person));
	check11 = head;
	while (check11 != NULL) {
		if (strcmp(check_user, check11->username) == 0) {
			d2 = 1;
			break;
		}
		check11 = check11->next;
	}
	if (d1 == 1 && d2 == 1) {
		struct sent_message *check_message1;
		struct received_message *check_message2;
		check_message1 = (struct sent_message*)malloc(sizeof(struct sent_message));
		check_message2 = (struct received_message*)malloc(sizeof(struct received_message));
		check_message1 = head1;
		check_message2 = head2;
		struct tm *ptr;
		time_t lt;
		lt = time(NULL);
		ptr = localtime(&lt);
		while (check_message1->next != NULL) {
			check_message1 = check_message1->next;
		}
		check_message1->next = (struct sent_message *)malloc(sizeof(struct sent_message));
		check_message1->next->next = NULL;
		check_message1->next->message = (char *)malloc((strlen(message1)) * sizeof(char));
		check_message1->next->rec_user = (char *)malloc((strlen(user1)) * sizeof(char));
		check_message1->next->sen_user = (char *)malloc((strlen(check_user)) * sizeof(char));
		check_message1->next->time_message = (char *)malloc((strlen(asctime(ptr))) * sizeof(char));
		strcpy(check_message1->next->message, message1);
		strcpy(check_message1->next->rec_user, check9->username);
		strcpy(check_message1->next->sen_user, check11->username);
		strcpy(check_message1->next->time_message, asctime(ptr));
		while (check_message2->next != NULL) {
			check_message2 = check_message2->next;
		}
		check_message2->next = (struct received_message *)malloc(sizeof(struct received_message));
		check_message2->next->next = NULL;
		check_message2->next->message = (char *)malloc((strlen(message1)) * sizeof(char));
		check_message2->next->rec_message = (char *)malloc((strlen(user1)) * sizeof(char));
		check_message2->next->sen_message = (char *)malloc((strlen(check_user)) * sizeof(char));
		check_message2->next->time_message= (char *)malloc((strlen(asctime(ptr))) * sizeof(char));
		strcpy(check_message2->next->message, message1);
		strcpy(check_message2->next->rec_message, user1);
		strcpy(check_message2->next->sen_message, check_user);
		check_message2->next->A = 0;
		strcpy(check_message2->next->time_message, asctime(ptr));
		printf("your message sucsesfully was sent\n");
	}
	else if (d1 == 0 || d2 == 0) {
		printf("there is a problem\n");
	}
}
void show_sent_message(char *check_user, struct sent_message *head1,char *user1) {
	struct sent_message *check_message3;
	check_message3 = (struct sent_message*)malloc(sizeof(struct sent_message));
	check_message3 = head1;
	while (check_message3 != NULL) {
		if (strcmp(check_message3->sen_user, check_user) == 0) {
			if (strcmp(check_message3->rec_user, user1) == 0) {
				printf("%s\n%s\n", check_message3->rec_user, check_message3->message);
				if (check_message3->time_message != '\0')
					printf("%s", check_message3->time_message);
			}
			}
		check_message3 = check_message3->next;
	}
}
void show_received_message(char *check_user, struct received_message *head2,char *user1) {
	struct received_message *check_message4;
	check_message4 = (struct received_message*)malloc(sizeof(struct received_message));
	check_message4 = head2;
	while (check_message4 != NULL) {
		if (strcmp(check_message4->rec_message, check_user) == 0) {
			if (strcmp(check_message4->sen_message, user1) == 0) {
				printf("%s\n%s\n", check_message4->sen_message, check_message4->message);
				if (check_message4->time_message != '\0')
					printf("%s", check_message4->time_message);
				check_message4->A = 1;
			}
			}
		check_message4 = check_message4->next;
	}
}
void show_info(struct person *head) {
	struct person *check5;
	check5 = (struct person*)malloc(sizeof(struct person));
	check5= head;
	while (check5 != NULL) {
		printf("%s\n", check5->username);
		check5= check5->next;
	}
}
void show_about(struct person *head,char *user1) {
	struct person *check7;
	int c2 = 0;
	check7 = (struct person*)malloc(sizeof(struct person));
	check7= head;
	while (check7 != NULL) {
		if (strcmp(check7->username, user1) == 0) {
			printf("%s\n", user1);
			printf("%s\n", check7->phonenumber);
			c2 = 1;
			break;
		}
		else {
			check7= check7->next;
			continue;
		}
	}
	if (c2 == 0)
		printf("this username does not exist\n");
}
void write_in_file(struct person *head, struct sent_message *head1, struct received_message *head2,char *check_user) {
	struct person *check15;
	check15 = (struct person*)malloc(sizeof(struct person));
	struct sent_message *check_message6;
	check_message6 = (struct sent_message*)malloc(sizeof(struct sent_message));
	struct received_message *check_message7;
	check_message7 = (struct received_message*)malloc(sizeof(struct received_message));
	check15 = head;
	check_message6 = head1;
	check_message7 = head2;
	FILE *file = fopen("data.csv", "w");
	while (check15 != NULL) {
		fprintf(file, "%s,%s,%s,", check15->username, check15->password, check15->phonenumber);
		check15 = check15->next;
	}
	fprintf(file, "%c", '\n');
	while (check_message6 != NULL) {
		fprintf(file, "%s,%s,%s,", check_message6->message, check_message6->rec_user, check_message6->sen_user);
		check_message6 = check_message6->next;
	}
	fprintf(file, "%c", '\n');
	while (check_message7 != NULL) {
		fprintf(file, "%s,%s,%s,", check_message7->message, check_message7->rec_message, check_message7->sen_message);
		check_message7 = check_message7->next;
	}
	fclose(file);
}
void edit_username(char *check_user,char *user1,struct person *head) {
	struct person *check2;
	check2 = (struct person *)malloc(sizeof(struct person));
	check2 = head;
	while (check2 != NULL) {
		if (strcmp(check2->username, check_user) == 0) {
			check2->username = (char *)realloc(check2->username, (strlen(user1)) * sizeof(char));
			strcpy(check2->username, user1);
		}
		check2 = check2->next;
	}
}
void edit_password(char *check_user, char *user1, struct person *head) {
	struct person *check4;
	check4 = (struct person *)malloc(sizeof(struct person));
	check4 = head;
	while (check4 != NULL) {
		if (strcmp(check4->username, check_user) == 0) {
			check4->password = (char *)realloc(check4->password, (strlen(user1)) * sizeof(char));
			strcpy(check4->password, user1);
		}
		check4 = check4->next;
	}
}