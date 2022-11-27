/*
*  Qiu Xuanluo
*  At 7 a.m. Beijing time on November 27
*  vioercer@outlook.com
*  Hide Mas OS desktop icon tool.   
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
	int ish;
	char off_icons[114] = "defaults write com.apple.finder CreateDesktop -bool false && killall Finder";
	char  on_icons[114] = "defaults write com.apple.finder CreateDesktop -bool true  && killall Finder";

	printf("\nTurn display off or on.\n\n");
	printf("(1) Display icons.\n");
	printf("(2) The icon is not displayed.\n");

	printf("-> ");
	scanf("%d", &ish);

	(ish==1)?system(on_icons):system(off_icons);

	return 0;
}
