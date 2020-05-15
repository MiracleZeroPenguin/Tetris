#ifndef COMPILE_MENU
#define COMPILE_MENU

#define unDefinedMenu 0
#define definedMenu 1
#define inputing 2
#define playing 3

#define registerMode 1
#define loginMode 2

int isShowingInfo; // �Ƿ�������ʾ�û���Ϣ 

static int isDefined = 0; // �û��Ƿ��¼ 
static int nowMenuMode; // ��ǰ�˵�ģʽ ��δ��¼����¼�������С���Ϸ�У� 
static int inputMode; // ����ģʽ��ע�����롢��¼���룩 
static double winwidth, winheight;   // ���ڳߴ�
static char results[200] = ""; // �����ַ����� 

/* 
 * ��������newUser 
 * ���ܣ��½��û� 
 */
void newUser();

/* 
 * ��������findUser 
 * ���ܣ�ʹ�������û� 
 */
void findUser();

/* 
 * ��������CharEventForMenu 
 * ���ܣ� ���ַܷ�����Բ˵����书�ܵ��ַ���Ϣ������ 
 * ����: ch - �ַ���Ϣ 
 */
void CharEventForMenu(char ch);

/* 
 * ��������solveDefined 
 * ���ܣ� ���ַܷ�������ѵ�¼�˵����ַ���Ϣ������ 
 * ����: ch - �ַ���Ϣ 
 */
void solveDefined(char ch);

/* 
 * ��������solveUndefined 
 * ���ܣ� ���ַܷ������δ��¼�˵����ַ���Ϣ������ 
 * ����: ch - �ַ���Ϣ 
 */
void solveUndefined(char ch);

/* 
 * ��������solveInputing
 * ���ܣ� ���ַܷ�����������е��ַ���Ϣ������ 
 * ����: ch - �ַ���Ϣ 
 */
void solveInputing(char ch);

/* 
 * ��������KeyboardEventForMenu
 * ���ܣ� ���ַܷ������������̵ļ�����Ϣ������ 
 * ����: key - �ǰ��»����ɿ� 
 *       event - ������λ 
 */
void KeyboardEventForMenu(int key,int event);

/* 
 * ��������startMenu
 * ���ܣ� ��ʾ�˵��������г�ʼ�� 
 * ����: x - �����Ĳ˵�ģʽ (0 :δ��¼ģʽ || 1 : �ѵ�¼ģʽ) 
 */
void startMenu(int x);

/* 
 * ��������inputBox
 * ���ܣ� ��ʾ������桢��������س�ʼ�� 
 */
void inputBox();

/* 
 * ��������display 
 * ���ܣ� �Ե�ǰ�������ˢ�� 
 */
void display();

/* 
 * ��������endInput 
 * ���ܣ� �� inputBox���ʹ�ã����ڽ������� 
 */
void endInput();

/* 
 * ��������logOut 
 * ���ܣ� �ǳ���ǰ�û� 
 */
void logOut();

/* 
 * ��������openHelp 
 * ���ܣ� �򿪰����ĵ� 
 */
void openHelp();

/* 
 * ��������switchUserInfo 
 * ���ܣ� �л��û���Ϣ��ʾ״̬ 
 */
void switchUserInfo();

/* 
 * ��������drawReturn 
 * ���ܣ� ���Ʒ��ذ�ť 
 */
void drawReturn();
#endif
