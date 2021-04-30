#include<stdio.h>
#include<string.h>

int main(){
	char data[25], frame[10];
	int i,j, n=0, num_frames, count=0, frame_size=0, data_size=0;

	printf("Enter the data to be sent\n");
	scanf("%s", data);
	data_size= strlen(data);

	printf("Enter the size of frame to be created\n");
	scanf("%d", &frame_size);

	while(n<data_size){
		for(i=n; i<n+frame_size; i++){
			printf("%c", data[i]);
		}
		printf("\n");
		n+=frame_size;
	}
	return 0;
}