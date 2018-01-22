import java.util.*;
class Process
{
	HashMap<Integer, Integer> a;
	int pno;
	int frames;
}
class paging
{
	static int allocate(int pnum,int[] memory)
	{
		for(int i=0;i<100;i++)
		{
			if(memory[i]==0)
			{
				memory[i]=pnum+1;
				return i;
			}
		}
		return -1;
	}
	public static void main(String args[])
	{
		Scanner s=new Scanner(System.in);
		boolean flag=true;int fsize=20, pnum=0;
		int memory[]=new int[100];
		Process[] processes=new Process[100];
		for(int i=0;i<100;i++)
		{
			memory[i]=0;
			processes[i]=new Process();
		}
		while(flag)
		{
			System.out.println("1. Add Process\n2. Kill Process\n3. List Processes\n4. Exit");
			System.out.println("Enter your choice:");
			int choice=s.nextInt();
			switch(choice)
			{
				case 1:
				System.out.println("Enter process size:");
				int psize=s.nextInt();
				int fno=(int)Math.ceil((float)psize/((float)fsize));
				HashMap<Integer, Integer> t=new HashMap<Integer, Integer>();
				int page_no=1;
				int x=allocate(pnum,memory);
				if(x==-1)
				{
					System.out.println("Memory full! No more processes!");
				}
				else
				{
					t.put(page_no++,x);
					for(;page_no<=fno;page_no++)
					{
						x=allocate(pnum,memory);
						t.put(page_no,x);
					}
					processes[pnum].frames=fno;
					processes[pnum].pno=pnum+1;
					processes[pnum++].a=t;
				}
				break;
				case 2:
				System.out.println("Enter process number:");
				int pno=s.nextInt();
				if(pno>=100||pno<=0)
					System.out.println("No such process!");
				else
				{
					if(processes[pno-1].a==null)
						System.out.println("No such process!");
					else
					{
						HashMap<Integer,Integer> temp;
						temp=processes[pno-1].a;
						for(int i=1;i<=processes[pno-1].frames;i++)
						{
							if(temp.get(i)!=-1)
								memory[temp.get(i)]=0;
						}
						processes[pno-1].a=null;
						System.out.println("Process killed!");
					}
				}
				break;
				case 3:
					for(int p=0;p<100;p++)
					{
						HashMap<Integer,Integer> temp=processes[p].a;
						if(temp!=null)
						{
							System.out.println("Process "+processes[p].pno);
							for(int i=1;i<=processes[p].frames;i++)
								System.out.println("Page "+i+"\n"+(processes[p].a.get(i)+1));
						}
					}
				
				break;
				case 4:
				flag=false;
				break;
				default:System.out.println("Invalid choice!");
			}
		}
	}
}