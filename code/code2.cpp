/*
10942208 ���y�w 
DS2ex1_10942208
�W���{���X 
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>

using namespace std ;

class Deap {
	/* ���V��n */
	private:
		
		struct heapItemType {
			
			int serial_num ; // �Ǹ� 
			int numstu; //number of student �ǥͼ� 
			string sname; //school name �ǮզW�� 
			string dname; //department name  ��t�W�� 
			string type; //day or night �鶡/�i�קO 
			string level; //grad or ungrad ���ŧO 
			
			
			
		}; // heapItemType
		
		
		
		int bottomIndex() { // ���obottom��index . index[0] no data
			if( DoubleEndHeap.size() > 1 ) return DoubleEndHeap.size() ;
		} // bottomIndex()
		
 
		
		int judge_exp( int index ) { // �P�_���� 
			int level = 0;
    		while (index > 0) {
        		index = (index - 1) / 2; 
        		level++;
    		}
    		return level;
		} // judge_exp()
		 
		char Judge_dir( int index ) {
			/* �P�_INDEX�O���l��B�٬O�k�l�� */ 
			int last = 1 ;
			for ( int n = 0 ; n < judge_exp( index ) ; n++ ) {
				last *= 2 ;
			} // for
			last = (last-1) + (last/2) ;
			
			if( index < last ) return 'L' ;
			else return 'R' ;
		}

		vector<heapItemType> DoubleEndHeap ; // ���V��n��Ƶ��c
	public:
		
		void reset() {
			DoubleEndHeap.clear(); // �M������n 
			heapItemType dummy ;
			DoubleEndHeap.push_back(dummy) ;  // �Y�`�I�O�Ū� 
		} // reset()	
		Deap() {
//			reset();
			
		} // Deap
		

		
		void prt_bottom_leftmost() {
			/* �L��� */
			cout << "<DEAP>" << endl ;
			//cout << "root: [" << maxHeap[0].serial_num << "] " << maxHeap[0].numstu  << endl ;
			cout << "bottom:	[" << DoubleEndHeap[this->bottomIndex()-1].serial_num << "] " << DoubleEndHeap[this->bottomIndex()-1].numstu  << endl ;
			
			int level = judge_exp( this->bottomIndex()-1) ; // ��
			int level_num = 1 ;
			for( int i = 0 ; i < level ; i++ ) level_num *= 2 ;
			
			//cout <<  level << endl ; 
			int leftest = level_num - 1 ;
			//cout <<  level_num << endl ; 
			cout << "leftmost bottom: [" << DoubleEndHeap[leftest].serial_num << "] " << DoubleEndHeap[leftest].numstu  << endl ;
			
		} // prt_root()
		
		bool IsEmpty() {
			if( DoubleEndHeap.size() <= 1 ) return true ;
			else false ;
		} // heapIsEmpty()
		
		void reBuildup( char max_min, int index ) {
			int father_pos = (index-1)/2 ;
			
			if( max_min == 'm' ) {
				
				while( DoubleEndHeap[father_pos].numstu < DoubleEndHeap[index].numstu && father_pos != 0 ) {
					// �Φbmax��A�V�W��z 
					//cout << DoubleEndHeap[index].numstu << "�洫" << DoubleEndHeap[father_pos].numstu << endl ; 
					heapItemType tmp = DoubleEndHeap[father_pos] ;
					DoubleEndHeap[father_pos] = DoubleEndHeap[index] ;
					DoubleEndHeap[index] = tmp ;
					index = father_pos ;
					father_pos = (index-1)/2 ;
				} // while
				
			}else {
				while( DoubleEndHeap[father_pos].numstu > DoubleEndHeap[index].numstu && father_pos != 0 ) {
					// �Φbmin��A�V�W��z 
					//cout << DoubleEndHeap[index].numstu << "�洫" << DoubleEndHeap[father_pos].numstu << endl ; 
					heapItemType tmp = DoubleEndHeap[father_pos] ;
					DoubleEndHeap[father_pos] = DoubleEndHeap[index] ;
					DoubleEndHeap[index] = tmp ;
					index = father_pos ;
					father_pos = (index-1)/2 ;
				} // while
			}
		} // reBuildup()
		
		void InsertItem( int serial_num , int numstu, string dname, string sname, string type, string level ) {
			/* ���b���l��ڥk�l�𪺱��� */ 
			/*
			 * ���b���l��A���L�����I�A�Ѥ��I�N��
			 * �p�G��(�s���I)�j��k�Nswap�A�s���I�i��ܤj�A�åB�V�Wrebuildup�A 
			 * ���L�hmin�k�l��item�����N�bbuttom�B�����`�I�j���ݭn�A�ܰ� 
			 * �p�G�S��swap,���i�ӥi��ܤp�ҥH�n�V�Wrebuild 
			 *
			 *   
			 * ���b�k�l�ơA���������I
			 * �p�G���Jitem�p�󥪴Nswap�A�k�l��n�V�Wrebuildup�A�s���I�i��ܤp 
			 * �k������`�I���ӴN����p�ҥH���ΰ� 
			 * �p�G�S��swap,���i�ӥi��ܤj�ҥH�n�V�Wrebuild 
			 */
			heapItemType add_item ;
			add_item.serial_num = serial_num ;
			add_item.numstu = numstu ;
			add_item.dname = dname ;
			add_item.sname = sname ;
			add_item.type = type ;
			add_item.level = level ;
			
			DoubleEndHeap.push_back(add_item) ;
			if( this->Judge_dir(serial_num) == 'L' ) { // ���J����min 
				
				//cout << "���l�𦬨�" <<  serial_num << "\t" <<  numstu  << endl ;
				
				int map_pos = 1 ;// ��M�`�I��m 
				
				for( int i = 1 ; i < this->judge_exp(serial_num) ; i++ ) map_pos *= 2 ;
				
				map_pos += serial_num ;
				//cout << serial_num << "��M�`�I" << map_pos << endl ; 
				
				if( DoubleEndHeap.size() <= map_pos ) { // �p�G�S����M�`�I 
					//cout << "�S����M�`�I" << endl ; 
					int father_pos ; // ��M�`�I������
					father_pos = (map_pos-1)/2 ;
					
					if( father_pos != 0) {
						//cout << "�ڧ�L��" << father_pos << "\t" << DoubleEndHeap[father_pos].numstu << endl ;
						
						if( DoubleEndHeap[father_pos].numstu < DoubleEndHeap[serial_num].numstu ) { // swap && rebuild // ��M�I���ˤp��{�b 
							// cout << DoubleEndHeap[serial_num].numstu << "�洫" << DoubleEndHeap[father_pos].numstu << endl ; 
							heapItemType tmp = DoubleEndHeap[father_pos] ;
							DoubleEndHeap[father_pos] = DoubleEndHeap[serial_num] ;
							DoubleEndHeap[serial_num] = tmp ;
							
							this->reBuildup( 'm', father_pos ) ;//�V�Wrebuild 
						} // if
						else {
							//cout << "��L���p,��a����" << endl; 
							this->reBuildup( 'a', serial_num ) ;
						}
						
					}
					
				}
				else { // ���i�঳��M�I 
				}
				
				
				
			}else{ // ���b�k�l��
				//cout << "�k�l�𦬨�" <<  serial_num << "\t" <<  numstu  << endl ;
				// ���Jitem�p�󥪴Nswap�A�k�l��n�V�Wrebuildup
				int map_pos = 1 ;// ��M�`�I��m 
				for( int i = 1 ; i < this->judge_exp(serial_num) ; i++ ) map_pos*= 2 ;
				
				map_pos = serial_num - map_pos;
				//cout << serial_num << "��M�`�I" << map_pos << endl ; 
				
				if( DoubleEndHeap[map_pos].numstu > DoubleEndHeap[serial_num].numstu ) {
					//cout << DoubleEndHeap[serial_num].numstu << "�洫" << DoubleEndHeap[map_pos].numstu << endl ; 
					
					heapItemType tmp = DoubleEndHeap[map_pos] ;
					DoubleEndHeap[map_pos] = DoubleEndHeap[serial_num] ;
					DoubleEndHeap[serial_num] = tmp ;
					this->reBuildup( 'a', map_pos ) ;
				}
				else reBuildup( 'm', serial_num ) ;
				
			}

			
		} // InsertItem() �v�@���J 
		
		
		int reHeapDown( int index ) {
			// �l�`�I�O index*2+1  index*2+2
			// case1 ��Ӹ`�I�s�b case2 �u�����`�I�s�b 
			// case1 ������k���I�A�Aswap
			// until �l�`�I����ۤv�por���츭�`�I  
			//int left_child = index*2+1 ;
			//int right_child = index*2+2 ;
			
			//heapItemType pop_item ;
			
			if( index*2+2 <= DoubleEndHeap.size() ) { // ��Ӹ`�I�s�b
			
				if( DoubleEndHeap[index*2+2].numstu <= DoubleEndHeap[index*2+1].numstu && DoubleEndHeap[index].numstu < DoubleEndHeap[index*2+1].numstu ) { // ���j��k 
					heapItemType tmp = DoubleEndHeap[index] ;
					DoubleEndHeap[index] = DoubleEndHeap[index*2+1] ;
					DoubleEndHeap[index*2+1] = tmp ;
					//cout <<"������" <<  index << "	swap	" << index*2+1 << endl ;
					index = index*2+1 ;
					
					
				} 
				else if( DoubleEndHeap[index*2+2].numstu > DoubleEndHeap[index*2+1].numstu && DoubleEndHeap[index].numstu < DoubleEndHeap[index*2+2].numstu ) {
					heapItemType tmp = DoubleEndHeap[index] ;
					DoubleEndHeap[index] = DoubleEndHeap[index*2+2] ;
					DoubleEndHeap[index*2+2] = tmp ;
					//cout <<"���k��" <<  index << "	swap	" << index*2+2 << endl ;
					index = index*2+2 ;
					
					
				}
				else {
					return index ;
				}
			}else if ( index*2+1 <= DoubleEndHeap.size() ) { // �u�����`�I�s�b
				if( DoubleEndHeap.size() == 2 ) {
					//pop_item = DoubleEndHeap[1] ; 
					return index ;
				}else {
					if( DoubleEndHeap[index].numstu < DoubleEndHeap[index*2+1].numstu ) {
						heapItemType tmp = DoubleEndHeap[index] ;
						DoubleEndHeap[index] = DoubleEndHeap[index*2+1] ;
						DoubleEndHeap[index*2+1] = tmp ;
						//cout <<"������" <<  index << "	swap	" << index*2+1 << endl ;
						index = index*2+1 ;
					}
					else {
						return index ;
					}
				}
			}
			else {
				//cout << "�S���l�I�F" << endl ; 
				return index ;
			}
			//cout << "�ثe�O�I:		" << index << endl; 
			return reHeapDown( index ) ;
			
			
		} //  ���Ureheap 

		heapItemType delete_max() {
			// case 1 �Ѱߤ@���`�I
			// case 2 �Ĥ@�k�`�I�٦s�b
			heapItemType pop_item ;
			int map_pot = 1 ; 
			
			if( DoubleEndHeap.size() == 2 ) { // ���F�̫�@�I 
				pop_item = DoubleEndHeap[1];
			} else { // ��L���p���O DoubleEndHeap[2] ���̤j�� 
				//	cout<< DoubleEndHeap[2].numstu  << endl ; 
				pop_item = DoubleEndHeap[2] ; 
				//cout << DoubleEndHeap[2].numstu <<	"swap	"  << DoubleEndHeap[DoubleEndHeap.size()-1].numstu << endl ;
				
				DoubleEndHeap[2] = DoubleEndHeap[DoubleEndHeap.size()-1] ;
				DoubleEndHeap.pop_back(); 
				//cout << "�i��O�d�b�o01" << endl ;
				//cout<< DoubleEndHeap[2].numstu  << endl ; 
				int index = this->reHeapDown(2) ; // �ثe��index 
				//cout << "�i��O�d�b�o02" << endl ;
				int level = this->judge_exp( index ) ;
				for( int i = 1 ; i < level ; i++ ) map_pot *= 2;
				map_pot = index - (map_pot) ;
				//cout<< "�̫�گ��b" << index << endl ; 
				//cout<< "�����`�I" <<  map_pot << endl ; 
				
				if( DoubleEndHeap[map_pot].numstu > DoubleEndHeap[index].numstu ) { // ����ڤj 
					heapItemType tmp = DoubleEndHeap[index] ;
					DoubleEndHeap[index] = DoubleEndHeap[map_pot] ;
					DoubleEndHeap[map_pot] = tmp ;
					this->reBuildup( 'n', map_pot ) ;
				}else {
					int map_pot_leftch = map_pot*2+1 ;
					int map_pot_rightch = map_pot*2+2 ;
					if( map_pot_rightch <= DoubleEndHeap.size()) {
						if( DoubleEndHeap[map_pot_rightch].numstu > DoubleEndHeap[map_pot_leftch].numstu && DoubleEndHeap[index].numstu < DoubleEndHeap[map_pot_rightch].numstu) { // ���l�`�I��ڤj 
							heapItemType tmp = DoubleEndHeap[index] ;
							DoubleEndHeap[index] = DoubleEndHeap[map_pot_rightch] ;
							DoubleEndHeap[map_pot_rightch] = tmp ;
						}else if( DoubleEndHeap[map_pot_rightch].numstu <= DoubleEndHeap[map_pot_leftch].numstu && DoubleEndHeap[index].numstu < DoubleEndHeap[map_pot_leftch].numstu ) {
							heapItemType tmp = DoubleEndHeap[index] ;
							DoubleEndHeap[index] = DoubleEndHeap[map_pot_leftch] ;
							DoubleEndHeap[map_pot_leftch] = tmp ;		
						}
						else {
							
						}
					}else if( map_pot_leftch <= DoubleEndHeap.size() ) {
						if( DoubleEndHeap[index].numstu < DoubleEndHeap[map_pot_leftch].numstu) { // ���l�`�I��ڤj 
							heapItemType tmp = DoubleEndHeap[index] ;
							DoubleEndHeap[index] = DoubleEndHeap[map_pot_leftch] ;
							DoubleEndHeap[map_pot_leftch] = tmp ;
						}
						else {
							
						}
					}

				}

			}
			
			//cout << "fin " << endl ;
			return pop_item ;
		} // �R���̤j�� 
		
//		int index = 2 ;
		
		void topK( int k ) { // �R���ek�ӳ̤j�� 
			
			
			//cout << "�I�s�R�����" << endl ; 
			for( int index = 1 ; index <= k ; index++ ) {
				heapItemType pop_item = delete_max() ;
				cout << "Top" << setw(4) << index <<  ": " << "[" << pop_item.serial_num << "] " << pop_item.sname << pop_item.dname << "," << pop_item.type << "," << pop_item.level << "," << pop_item.numstu << endl ;
			}

		} 
		
		void prt() {
			for(int i = 1 ; i < this->bottomIndex() ; i++ ) cout <<  DoubleEndHeap[i].serial_num << "\t" << DoubleEndHeap[i].numstu << endl  ;
		} // 
}; // Deap


class MaxHeap {
	private:
		
		struct heapItemType {
			
			int serial_num ; // �Ǹ� 
			int numstu; //number of student �ǥͼ� 
			
		}; // heapItemType
		
		vector<heapItemType> maxHeap ; // �̤j��n��Ƶ��c
		
		int getbottomPos() { // ���obottom��index 
			if( maxHeap.size() > 0 ) return maxHeap.size()-1 ;
		} // getbottomPos()
		
		void reset() {
			maxHeap.clear();
		} // reset()
		
		int judge_exp( int index ) { // �P�_���� 
			int level = 0;
    		while (index > 0) {
        		index = (index - 1) / 2; 
        		level++;
    		}
    		return level;
		} // judge_exp()
		
	public:
		
		MaxHeap() {
			reset();
		} // Heap()
		
		void prt_root_bottom_leftmost() {
			/* �L��� */
			cout << "<max heap>" << endl ;
			cout << "root: [" << maxHeap[0].serial_num << "] " << maxHeap[0].numstu  << endl ;
			cout << "bottom:	[" << maxHeap[this->getbottomPos()].serial_num << "] " << maxHeap[this->getbottomPos()].numstu  << endl ;
			
			/* ��n-1�A��������1 �Y�O������m */ 
			int level = judge_exp( this->getbottomPos() ) ;
			int level_num = 1 ;
			for( int i = 0 ; i < level ; i++ ) level_num *= 2 ;
			int leftest = level_num - 1 ;

			cout << "leftmost bottom: [" << maxHeap[leftest].serial_num << "] " << maxHeap[leftest].numstu  << endl ;
		} // prt_root()
		
		bool heapIsEmpty() {
			if( maxHeap.size() == 0 ) return true ;
		} // heapIsEmpty()
		
		void heapInsert( int serial_num , int numstu ) {
			/* 
			 * �N�s������mbottom 
			 * �V���`�I��� 
			 * ���줣�j����`�I 
			*/
			heapItemType newItem ;
			newItem.serial_num = serial_num ;
			newItem.numstu = numstu ;
			maxHeap.push_back(newItem) ; // �K�[�bbottom
			
			int bottom_pos = this->getbottomPos() ;
			int grand_pos = (bottom_pos-1)/2 ;
			
			while( (maxHeap[bottom_pos].numstu > maxHeap[grand_pos].numstu) && bottom_pos > 0 ) {
				heapItemType tmp ;
				tmp = maxHeap[bottom_pos] ;
				maxHeap[bottom_pos] = maxHeap[grand_pos] ;
				maxHeap[grand_pos] = tmp ;
				
				bottom_pos = grand_pos ;
				grand_pos = (bottom_pos-1)/2 ;
			}
			
		} // heapInsert() �v�@���J 
		
		void heapDelete() {
			/* ����root,�ç�bottom���W�h(semi-heap),�Nroot�t�m�쥿�T��m*/
			/* unfinished */ 
			maxHeap[0] = maxHeap[this->getbottomPos()] ;
			maxHeap.pop_back() ;
			
		} // heapDelete();
		
		void heapRebuild() {
			/* �q���U�V�W�v�B���㦨�̤j��n */
			int cur = this->getbottomPos(); // �{�b��m 
			int cur_grand ; // ���`�I��m 
	
			while( cur > 0 ) { // ����root���� 
				
				cur_grand = (cur-1)/2;
				
				if( maxHeap[cur].numstu > maxHeap[cur_grand].numstu ) { 
				// swap
					//cout << "�洫" <<  maxHeap[cur].numstu <<  "&&" << maxHeap[cur_grand].numstu << endl ; 
					heapItemType tmp ;
					tmp = maxHeap[cur] ;
					maxHeap[cur] = maxHeap[cur_grand] ;
					maxHeap[cur_grand] = tmp ;
				}
				cur-- ;
			}
			
		} // heapRebuild()
		
		void prt() {
			for(int i = 0 ; i <= this->getbottomPos() ; i++ ) cout <<  maxHeap[i].serial_num << "\t" << maxHeap[i].numstu << endl  ;
		} // 
		 
}; // end Heap

class SchoolList {
	
	private:
		
		struct schoolType { // ��ƫ��O 
			
			string cityname ; // �����W�� 
			string system; // ��t�O 
			string sname; //school name �ǮզW�� 
			string dname; //department name  ��t�W�� 
			string type; //day or night �鶡/�i�קO 
			string level; //grad or ungrad ���ŧO 
			int schnum ; // school num �ǮեN�X 
			int depnum ; // department num �t�ҽs�� 
			int numstu; //number of student �ǥͼ� 
			int numprof; //number of professor �Юv�� 
			int numgrad; //number of graduates �W�Ǧ~�ײ��~�ͼ�
			int serial_num ;
			 
		}; 
		
		int row = 0 ;
		string title = ""; // ���D 
		string fileID; // �ɮ׽s�� 
		
		vector<schoolType> allinfo; //dynamic allocation that save school information
		
		void reset() {
			allinfo.clear();
		}//end reset
		
		Deap deap_heap ;
		int re = 0 ;
	public:
		
		SchoolList() {
			reset(); 
			
		}
			
		~SchoolList() {
			reset();
		}
		
		bool readFile() {
			
			//Deap deap_heap ;
			allinfo.clear();
			fstream inFile;
			string fileName;
			this -> reset();
			cout << endl << "Input a file number ([0] Quit): ";
			cin >> this -> fileID;
			fileName = "input" + fileID + ".txt";
			inFile.open(fileName.c_str()) ;
			if(!inFile.is_open()){
				cout << endl << "###" << fileName << " does not exist!###"<<endl;
				return false;
			}
			else{
				char cstr[255];				
				int fNo, pre, pos;
				title = "" ;
				row = 0 ;
				inFile.getline(cstr,255,'\n'); // �j�M�հ|�U�լ�t�O���p	
				inFile.getline(cstr,255,'\n'); // 105 �Ǧ~�� SY2016-2017	
				inFile.getline(cstr,255,'\n'); 
				
				title.assign(cstr);
				
				while(inFile.getline(cstr,255,'\n')) {  // �ĤT�C
					row++ ;
					schoolType oneR; // one data records �@���Ǯո�� 
					string buf,cut;
					
					fNo=0; // �@�檺�ĴX����� 
					pre=0; // �e�����L�h�֦r�� , �U�@�Ӱ_�l��m 
					
					
					buf.assign(cstr);
					
					do {
						pos = buf.find_first_of('\t' , pre); // �J�� '\t' ���r����m 
						cut = buf.substr(pre, pos-pre);  // �{�b��m - �_�l��m 
						
						switch(++fNo) {
							case 1 :
								oneR.schnum = atoi(cut.c_str());
							case 2:
								oneR.sname = cut;
								break;
							case 3:
								oneR.depnum = atoi(cut.c_str());
								break;
							case 4:
								oneR.dname = cut;
								break;
							case 5:	
								oneR.type = cut;
								break;
							case 6:
								oneR.level = cut;
								break;
							case 7: 
								oneR.numstu = atoi(cut.c_str());
								break;
							case 8:
								oneR.numprof = atoi(cut.c_str());
								break;
							case 9:
								oneR.numgrad = atoi(cut.c_str());
								break;
							case 10:
								oneR.cityname = cut;
								break;
							case 11:
								oneR.system = cut;
								break;
							default: 
								break;
						}
						pre = ++pos;
						
					}while((fNo < 12) && (pos > 0));//do
					
					oneR.serial_num = row ;
					this -> allinfo.push_back(oneR);
					
						
					
				} //while
				
				inFile.close();
			}//else
			
			if(!this->allinfo.size()) {
				cout << endl << "###Get nothing from the file" << fileName << "!###" <<endl;
				return false;
			}//if
			re = allinfo.size() ;
			
			return true;
		}//end readFile
		
		void printAllinfo() {
			cout << this->title << endl ;
			for(int i = 0 ; i < allinfo.size() ; i++) {
				
			
				cout << "[" << allinfo[i].serial_num << "]" << allinfo[i].schnum << '\t' << allinfo[i].sname << '\t' << allinfo[i].depnum << '\t' << allinfo[i].dname << '\t' << allinfo[i].type << '\t' << allinfo[i].level;
				cout <<'\t' << allinfo[i].numstu << '\t' << allinfo[i].numprof << '\t' << allinfo[i].numgrad << '\t' << allinfo[i].cityname << '\t' << allinfo[i].system <<  endl;
		
			}
		}
		
		void buildMaxHeap() {
			MaxHeap max_heap ;
			for( int i = 0 ; i < allinfo.size() ; i++ ) {
				max_heap.heapInsert( allinfo[i].serial_num, allinfo[i].numstu );
			} // for
			//max_heap.heapRebuild();
			//max_heap.prt(); // �C�L��n 
			max_heap.prt_root_bottom_leftmost();
		} // �إ߰�n 
		
		void buildEAHeap() {
			deap_heap.reset();
			for( int i = 0 ; i < allinfo.size() ; i++ ) {
				
				deap_heap.InsertItem( allinfo[i].serial_num, allinfo[i].numstu, allinfo[i].dname, allinfo[i].sname, allinfo[i].type, allinfo[i].level );
				//int serial_num , int numstu, string dname, string sname, string type, string level
			} // for
			//deap_heap.heapRebuild();
			//max_heap.prt(); // �C�L��n 
			deap_heap.prt_bottom_leftmost();
			
		} // �إ߰�n
		
		
		void topK() {
			//cout << "�`�@	" <<  this->allinfo.size();  
			int k = 0 ;
			//deap_heap.prt();
			
			if( re >= 1 && k <= re) {
				
				cout << endl << "Enter the value of K in" << "[1," << re << "]:" ;
				cin >> k ;
				if( k > re ) cout << "over boundary situation 1 : �@���R����Ѿl��Ƶ����٦h " << endl ; // �@���R�����Ƶ����٦h 
				else {
					// �I�stopK���
					deap_heap.topK( k ) ;
					re -= k ;
				}
			}
			else{
				cout << "over boundary situation 2 : �S��Ƶ��A�R�F" << endl ; // �L�k�A�R�� 
			}
			//cout << "�Ѿl���	" <<  re ; 
		} // TopK
		
}; //end SchoolList



int main() {
	int cmd = -1;
	SchoolList sch;
	string school_name = "" ;
	bool check = false ;
	do {
		
        cout << endl << "**** Heap Construction ********" << endl;
        cout << "* 0. Quit                     *" << endl;
        cout << "* 1. Build a max heap         *" << endl;
        cout << "* 2. Build a DEAP             *" << endl;
        cout << "* 3. Top-K maximums from DEAP *" << endl;
        cout << "*******************************" << endl;
        cout << "Input a choice(0, 1, 2, 3): ";
        cin >> cmd;
        switch(cmd){
        	case 0:
        		break;
			case 1:	
				if(sch.readFile()) sch.buildMaxHeap() ;
				break;
			case 2:
				if(sch.readFile()) {
					sch.buildEAHeap() ;
					check = true ;
				}
			break;
			case 3: 
				if( check ) {
					sch.topK()  ;
				}
				else cout << "build deap first !!!" ;
			break;
			default:
				cout << endl << "Command does not exist!" << endl << endl;
			break;
		}
		
	} while(cmd!=0);
	system("pause");
	return 0;
}
