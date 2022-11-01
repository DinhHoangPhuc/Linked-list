#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<string.h>

struct MonHoc {
	char maMH[10];
	char tenMh[20];
	int soTinChi;
	float diemTL, diemCuoiKi, diemMH;
};

struct NodeMH {
	MonHoc info;
	NodeMH* next;
};

struct SListMH {
	NodeMH* head;
	NodeMH* tail;
};

struct SinhVien {
	char maSV[11];
	char hoDem[26];
	char tenSV[9];
	int namSinh;
	float diemKQ;
	SListMH monHoc;
};

struct NodeSV {
	SinhVien info;
	NodeSV* next;
};

struct SListSV {
	NodeSV* head;
	NodeSV* tail;
};

void xuat1SV(SinhVien x);
void xuatSList(SListSV sl);
void createSList(SListSV& sl);
void themNodeVaoCuoiListSV(SListSV& sl, SinhVien x);
NodeSV* createNodeSV(SinhVien x);
void doc1MH(MonHoc& x, FILE* f);
NodeMH* createNodeMH(MonHoc x);
void themNodeVaoCuoiListMH(SListMH& sl, MonHoc x);
NodeSV* timThongTinSVXTheoTen(SListSV l, char tenSV[]);
void xuatThongTinSVX(SListSV l, char tenSV[]);
NodeSV* diemCuaSVXTheoMSSV(SListSV l, char maSoSV[]);
void sapXepDSSVTangDanTheoMSSV(SListSV& l);
void sapXepDSSVTangDanTheoTenSV(SListSV& l);
void xuat1MH(MonHoc x);

void main()
{
	int luachon;
	do
	{
		do
		{
			printf("\n");
			printf("------------------------------MENU------------------------------\n");
			printf("1. Doc danh sach tu file va in ra man hinh\n");
			printf("2. Cho biet thong tin cua sinh vien ten X\n");
			printf("3. Cho biet ho ten va diem ket qua cua sinh vien co ma so X\n");
			printf("4. Sap xep tang dan theo ma sinh vien\n");
			printf("5. Sap xep tang dan theo ten sinh vien\n");
			printf("0. Ket thuc chuong trinh\n");
			printf("Nhap lua chon cua ban: ");
			scanf_s("%d", &luachon);
		} while (luachon < 0);

		switch (luachon)
		{
		case 1:
		{
			SListSV sl;
			createSList(sl);
			printf("SList hien tai:\n");
			xuatSList(sl);
			break;
		}

		case 2:
		{
			SListSV sl;
			createSList(sl);
			printf("SList hien tai:\n");
			xuatSList(sl);
			char tenSV[20];
			rewind(stdin);
			printf("Nhap ten sinh vien: ");
			gets_s(tenSV, 20);
			xuatThongTinSVX(sl, tenSV);
			break;
		}

		case 3:
		{
			SListSV sl;
			createSList(sl);
			printf("SList hien tai:\n");
			xuatSList(sl);
			char maSoSV[20];
			rewind(stdin);
			printf("Nhap ma so sinh vien: ");
			gets_s(maSoSV, 20);
			NodeSV* p = diemCuaSVXTheoMSSV(sl, maSoSV);
			if (p != NULL)
				printf("Diem cua sinh vien co ma so %s la: %f\n", maSoSV, p->info.diemKQ);
			else
				printf("Khong tim thay sinh vien co ma so %s\n", maSoSV);
			break;
		}

		case 4:
		{
			SListSV sl;
			createSList(sl);
			printf("SList hien tai:\n");
			xuatSList(sl);
			sapXepDSSVTangDanTheoMSSV(sl);
			printf("SList sau khi sap xep:\n");
			xuatSList(sl);
			break;
		}

		case 5:
		{
			SListSV sl;
			createSList(sl);
			printf("SList hien tai:\n");
			xuatSList(sl);
			sapXepDSSVTangDanTheoTenSV(sl);
			printf("SList sau khi sap xep:\n");
			xuatSList(sl);
			break;
		}

		default:
			break;
		}
	} while (luachon > 0 && luachon <= 8);
}

void xuat1SV(SinhVien x)
{
	printf("\nMaSV\tHo dem\t\tTenSV\tNam sinh\tDiem KQ\n");
	printf("%s\t%s\t%s\t%d\t\t%f\n", x.maSV, x.hoDem, x.tenSV, x.namSinh, x.diemKQ);
	printf("Ma mon hoc\tTen mon hoc   \tSo tin chi\tDiem tieu luan\tDiem cuoi ki\tDiem mon hoc\n");
	NodeMH* q = x.monHoc.head;
	while (q != NULL)
	{
		/*printf("%s\t%s\t%d\t%f\t%f\t%f\n", q->info.maMH, q->info.tenMh, q->info.soTinChi, q->info.diemTL, q->info.diemCuoiKi, q->info.diemMH);*/
		xuat1MH(q->info);
		printf("\n");
		q = q->next;
	}
}

void xuat1MH(MonHoc x)
{
	printf("%-16s%-15s%10d%15.2lf%15.2lf%15.2lf\n", x.maMH, x.tenMh, x.soTinChi, x.diemTL, x.diemCuoiKi, x.diemMH);
	/*printf("%s\t\t%s\t\t%d\t%f\t%f\t%f\n", x.maMH, x.tenMh, x.soTinChi, x.diemTL, x.diemCuoiKi, x.diemMH);*/
}

void xuatSList(SListSV sl)
{
	int dem = 0;
	NodeSV* p = sl.head;
	while (p != NULL)
	{
		xuat1SV(p->info);
		/*printf("MaSV\tHo dem\t\tTenSV\tNam sinh\tDiem KQ\n");
		xuat1SV(p->info);
		dem++;
		if (dem == 1)
			printf("Ma mon hoc\tTen mon hoc\tSo tin chi\tDiem tieu luan\tDiem cuoi ki\tDiem mon hoc\n");
		NodeMH* q = p->info.monHoc.head;
		while (q != NULL)
		{
			xuat1MH(q->info);
			printf("\n");
			q = q->next;
		}*/
		p = p->next;
	}
}

NodeSV* createNodeSV(SinhVien x)
{
	NodeSV* p = new NodeSV;
	if (p == NULL)
		return NULL;
	p->info = x;
	p->next = NULL;
	return p;
}

void themNodeVaoCuoiListSV(SListSV& sl, SinhVien x)
{
	NodeSV* p = createNodeSV(x);
	if (sl.head == NULL)
		sl.head = sl.tail = p;
	else
	{
		sl.tail->next = p;
		sl.tail = p;
	}
}

void createSList(SListSV& sl)
{
	float tongDiemMonHoc = 0;
	int tongTinChi = 0;
	MonHoc a;
	SListMH l;
	/*l.head = l.tail = NULL;*/
	FILE* f = fopen("inputSinhVien.txt", "r");
	if (f == NULL)
	{
		printf("Loi file\n");
		return;
	}
	sl.head = sl.tail = NULL;
	int n1, n2;
	SinhVien x;
	fscanf_s(f, "%d\n", &n1);
	for (int i = 0; i < n1; i++)
	{
		fscanf_s(f, "%[^#]#%[^#]#%[^#]#%d#", x.maSV, sizeof(x.maSV), x.hoDem, sizeof(x.hoDem), x.tenSV, sizeof(x.tenSV), &x.namSinh);
		/*fscanf(f, "%[^\#]#%[^\#]#%[^\#]#%d#", x.maSV, x.hoDem, x.tenSV, &x.namSinh);*/
		fscanf_s(f, "%d\n", &n2);
		l.head = l.tail = NULL;
		for (int j = 0; j < n2; j++)
		{
			doc1MH(a, f);
			/*fscanf_s(f, "%[^#]#%[^#]#%d#%f#%f\n", a.maMH, sizeof(a.maMH), a.tenMh, sizeof(a.tenMh), &a.soTinChi, &a.diemTL, &a.diemCuoiKi);*/
			a.diemMH = a.diemTL * 0.3 + a.diemCuoiKi * 0.7;
			tongDiemMonHoc += a.diemMH * (float)a.soTinChi;
			tongTinChi += a.soTinChi;
			themNodeVaoCuoiListMH(l, a);
		}
		x.diemKQ = tongDiemMonHoc / (float)tongTinChi;
		x.monHoc = l;
		themNodeVaoCuoiListSV(sl, x);
	}
	fclose(f);
}

void doc1MH(MonHoc& x, FILE* f)
{
	fscanf_s(f, "%[^#]#%[^#]#%d#%f#%f\n", x.maMH, sizeof(x.maMH), x.tenMh, sizeof(x.tenMh), &x.soTinChi, &x.diemTL, &x.diemCuoiKi);
	/*fscanf(f, "%[^\#]#%[^\#]#%d#%f#%f\n", x.maMH, x.tenMh, &x.soTinChi, &x.diemTL, &x.diemCuoiKi);*/
}

NodeMH* createNodeMH(MonHoc x)
{
	NodeMH* p = new NodeMH;
	if (p == NULL)
		return NULL;
	p->info = x;
	p->next = NULL;
	return p;
}

void themNodeVaoCuoiListMH(SListMH& sl, MonHoc x)
{
	NodeMH* p = createNodeMH(x);
	if (sl.head == NULL)
		sl.head = sl.tail = p;
	else
	{
		sl.tail->next = p;
		sl.tail = p;
	}
}

NodeSV* timThongTinSVXTheoTen(SListSV l, char tenSV[])
{
	NodeSV* p = l.head;
	while (p != NULL)
	{
		if (strcmp(p->info.tenSV, tenSV) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

void xuatThongTinSVX(SListSV l, char tenSV[])
{
	NodeSV* p = timThongTinSVXTheoTen(l, tenSV);
	if (p != NULL)
		xuat1SV(p->info);
	else
		printf("Khong tim thay sinh vien ten %s\n", tenSV);
}

NodeSV* diemCuaSVXTheoMSSV(SListSV l, char maSoSV[])
{
	NodeSV* p = l.head;
	while (p != NULL)
	{
		if (strcmp(p->info.maSV, maSoSV) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

void sapXepDSSVTangDanTheoMSSV(SListSV& l)
{
	for (NodeSV* p = l.head; p != l.tail; p = p->next)
		for (NodeSV* q = p->next; q != NULL; q = q->next)
			if (strcmp(q->info.maSV, p->info.maSV) < 0)
			{
				SinhVien t = p->info;
				p->info = q->info;
				q->info = t;
			}
}

void sapXepDSSVTangDanTheoTenSV(SListSV& l)
{
	for (NodeSV* p = l.head; p != l.tail; p = p->next)
		for (NodeSV* q = p->next; q != NULL; q = q->next)
			if (strcmp(q->info.tenSV, p->info.tenSV) < 0)
			{
				SinhVien t = p->info;
				p->info = q->info;
				q->info = t;
			}
}