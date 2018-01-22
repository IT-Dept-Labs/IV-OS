import java.util.*;
class Page
{
	Page(int addr){
		next_addr=addr;
	}
	String content="Pages";
	int next_addr=-1;
}
class Process
{
	List<Page> pageList;
	int pno;
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
				List<Page> t=new LinkedList<Page>();
				int x=allocate(pnum,memory);
				if(x==-1)
				{
					System.out.println("Memory full!!");
				}
				else
				{
					Page p=new Page(x);
					t.add(p);
					for(int i=0;i<fno-1;i++)
					{
						x=allocate(pnum,memory);
						p=new Page(x);
						t.add(p);
					}
					processes[pnum].pno=pnum+1;
					processes[pnum++].pageList=t;
					System.out.println("Process added at "+x)

				}
				break;
				case 2:
				System.out.println("Enter process number:");
				int pno=s.nextInt();
				if(pno>=100||pno<=0)
					System.out.println("Process not found!!");
				else
				{
					if(processes[pno-1].pageList==null)
						System.out.println("Process not found");
					else
					{
						List<Page> temp=new LinkedList<Page>();
						temp=processes[pno-1].pageList;
						Iterator<Page> it=temp.iterator();
						while(it.hasNext())
							memory[it.next().next_addr]=0;

						processes[pno-1].pageList=null;
						System.out.println("Process killed!");
					}
				}
				break;
				case 3:
					for(int p=0;p<100;p++)
					{
						List<Page> temp=processes[p].pageList;
						if(temp!=null)
						{
							Iterator<Page> it=temp.iterator();
							System.out.println("Process "+processes[p].pno);
							int i=0;
							while(it.hasNext())
							{
								System.out.println("Page "+Integer.toString(++i));
								System.out.println((it.next().next_addr+1));
							}
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