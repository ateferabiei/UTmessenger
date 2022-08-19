#pragma once
struct person {
	char *username;
	char *phonenumber;
	char *password;
	struct person *next;
};

struct sent_message {
	char *rec_user;                         /*someone who received this message*/
	char *sen_user;                         /*someone who send this message*/
	char *message;
	char *time_message;                     /*when this message was sent*/
	struct sent_message *next;
};

struct received_message {
	char *sen_message;                      /*someone who sent this message*/
	char *rec_message;                      /*someone who received this message*/
	char *message;
	char *time_message;                     /*when this message was sent*/
	int A;
	struct received_message *next;
};




int signup(char *check_user, char *check_pass, char *check_phonenumber, struct person *head);
int check_size_password(char *check_pass);
int check_phonenumber_size(char *check_phonenumber);
int login(char *check_user, char *check_pass, struct person *head);
void show_info(struct person *head);
void show_about(struct person *head,char *user1);
int start_UTMESSAGER(struct person *head, char *check_user, struct sent_message *head1, struct received_message *head2);
void show_unread_message(struct received_message *head2, char *check_user);
void show_sent_message(char *check_user, struct sent_message *head1,char *user1);
void show_received_message(char *check_user, struct received_message *head2,char *user1);
void send_message(struct person *head, char *check_user, char *user1, struct sent_message *head1, struct received_message *head2, char *message1);
void write_in_file(struct person *head, struct sent_message *head1, struct received_message *head2, char *check_user);
void write_in_struct(struct person *head, struct sent_message *head1, struct received_message *head2, char *filecontent);
void read_from_file(struct person *head, struct sent_message *head1, struct received_message *head2);
void edit_username(char *check_user, char *user1, struct person *head);
void edit_password(char *check_user, char *user1, struct person *head);