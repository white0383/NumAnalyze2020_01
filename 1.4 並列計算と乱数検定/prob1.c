#include <stdio.h>
#include <omp.h>

//https://qiita.com/ktgw0316/items/23235dd2533f488be7da openmp clang 설정
//clang -Xpreprocessor -fopenmp -lomp prob1.c -o app1 => 내 pc
//gcc -fopenmp prob1.c -o app1 => 가상환경

int main() {
    //현재 이 문장이 실행되는 스레스 번호를 반환
  int th = omp_get_num_threads();
    //이 맥북은 최대 8스레드를 가진다
  int maxth = omp_get_max_threads();

  printf("threads : %d \n",th);
  printf("max threads : %d \n",maxth);

  int count = 1;
    //이 문장의 실행시간
  double time = omp_get_wtime();
  printf("%d A %lf\n",count,time);

  //예제 1 모든 8개의 스레드에서 동시에 실행한다!
  #pragma omp parallel 
  {
    th = omp_get_num_threads();
    time = omp_get_wtime();
    printf("threads : %d \n",th);
    count++;
    printf("%d B %lf\n",count,time);
  }
  printf("%d C\n",count);

  count = 1;
  printf("\n\n\n");

  //예제 2 8개의 스레드들이 for루프를 나눠서 한다
  #pragma omp parallel
  {
    #pragma omp for
    for(int i=0;i<24;i++)
    {
      time = omp_get_wtime();
      printf("%d %lf\n",i,time);
    }
  }

  //예제 3 8개중에 2개만 사용한다!
  #pragma omp parallel
  {
    #pragma omp sections
    {
      #pragma omp section
      {
        //section A
        count ++;
        printf("%d I am in section A! hello~ \n",count);
      }
      #pragma omp section
      {
        //section B
        count ++;
        printf("%d I am in section B! hi! \n",count);
      }
    }
  }

  //예제 4 동기 프로그래밍 barrier
  //모든 스레드에서 barrier 전에 있는걸 끝내기를 기다린다
  #pragma omp parallel
  {
    printf("A\n");
    #pragma omp barrier
    printf("B\n");
  }

  //예제 5 어떤 명령을 동시에 실행하는 것은 1스레드 뿐임
  return 0;
}