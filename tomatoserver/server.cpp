#include"chatroomserver.h"
#include"loginserver.h"
#include"ranklistserver.h"
#include"signupserver.h"
#include"rankchange.h"
int main() {
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)chatroomserver, NULL, NULL, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)loginserver, NULL, NULL, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ranklistserver,NULL, NULL, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)rankchange, NULL, NULL, NULL);
	signupserver();
}
