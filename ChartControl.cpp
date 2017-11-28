// ChartControl.cpp : implementation file
//

#include "stdafx.h"
#include "SatCon.h"
#include "ChartControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
#define XAXIS_SECTION_SUM 24
#define YAXIS_SECTION_SUM 5
#define TICKMARK_LENGTH	10	//刻度线长
#define FRAME_DISTANCE	30	//到边框的距离
#define	FRAME_X_DISTANCE	70	//x轴到边框的距离
/////////////////////////////////////////////////////////////////////////////
// CChartControl

CChartControl::CChartControl()
{
	m_pinfo=NULL;
}

CChartControl::~CChartControl()
{
}


BEGIN_MESSAGE_MAP(CChartControl, CWnd)
	//{{AFX_MSG_MAP(CChartControl)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChartControl message handlers

void CChartControl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(rect);
	InitCoordinate(rect);

	m_dc.CreateCompatibleDC(&dc);
	m_BitMap.CreateCompatibleBitmap(&m_dc,rect.Width(),rect.Height());
	CBitmap *pOldBit=m_dc.SelectObject(&m_BitMap);
	m_dc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));

	DrowCoor();
	DrawGraph();

	dc.BitBlt(0,0,rect.Width(),rect.Height(),&m_dc,0,0,SRCCOPY);	
	m_BitMap.DeleteObject();
	m_dc.DeleteDC();
	// Do not call CWnd::OnPaint() for painting messages
}
///初始化坐标系坐标
void CChartControl::InitCoordinate(CRect rect)
{
	m_origion.x=FRAME_X_DISTANCE;
	m_origion.y=rect.Height()-FRAME_DISTANCE;
	
	m_section.x=(rect.Width()-FRAME_X_DISTANCE-m_origion.x)/XAXIS_SECTION_SUM;
	m_section.y=(m_origion.y-FRAME_DISTANCE)/YAXIS_SECTION_SUM;
	
	m_Xend.x=m_origion.x+(m_section.x*XAXIS_SECTION_SUM);
	m_Xend.y=m_origion.y;
	
	m_Yend.x=m_origion.x;
	m_Yend.y=m_origion.y-(m_section.y*YAXIS_SECTION_SUM);


	m_unitY=(double)(m_origion.y-m_Yend.y)/YMax;

	m_unitX=(double)(m_Xend.x-m_origion.x)/86400;

	if(m_pinfo!=NULL)
	{
		if((m_pinfo->max-m_pinfo->min)>0)
		{
			m_unitY=(double)(m_origion.y-m_Yend.y)/(m_pinfo->max-m_pinfo->min);
			Yaxis=(m_pinfo->max-m_pinfo->min)/5;
			YaxisStr=m_pinfo->unit;
		}
	}
}
///画坐标轴///画坐标轴
void CChartControl::DrowCoor()
{

	m_dc.MoveTo(m_origion);
	m_dc.LineTo(m_Xend);
		
	m_dc.MoveTo(m_origion);
	m_dc.LineTo(m_Yend);
		
	DrawSection(XAXIS_SECTION_SUM, true);//画x坐标轴的刻度线和文字
	DrawSection(YAXIS_SECTION_SUM, false);//画y坐标轴的刻度线和文字
}
//画x坐标轴和y坐标轴的刻度线和文字
void CChartControl::DrawSection(int sum, bool XorY)
{
	CPoint point=m_origion;
	CPoint pointLine;
	CString str;
	CRect rect;
	int len;
	for(int i=0;i<=sum;i++)//Y轴刻度文字
	{
		if(XorY==true)//x轴
		{
			point.x=m_origion.x+i*m_section.x;
			pointLine.x=point.x;
			pointLine.y=point.y+TICKMARK_LENGTH;
			
			rect=CRect(point.x,point.y+10,point.x+30,point.y+30);//l,t,r,b文字位置
			str.Format("%d",i);
		}
		else//Y轴
		{
			point.y=m_origion.y-i*m_section.y;
			pointLine.x=point.x-TICKMARK_LENGTH;
			pointLine.y=point.y;
			str.Format("%d%s",i*Yaxis,YaxisStr);
			len=str.GetLength();
			rect=CRect(point.x-10-len*10,point.y-10,point.x-10,point.y+10);//l,t,r,b文字位置
			
		}
		m_dc.MoveTo(point);
		m_dc.LineTo(pointLine);
		m_dc.DrawText(str,rect,DT_BOTTOM);
	}
}
//画动态曲线图
void CChartControl::DrawGraph()
{
	POSITION posT=Tlist.GetHeadPosition();
	POSITION posD=Dlist.GetHeadPosition();
	int cou=Tlist.GetCount()-1;
	CPoint p;
	CTime t;
	CTime ot;
	CTimeSpan span;
	double d;
	if(cou>1)
	{
		ot=t=Tlist.GetNext(posT);
		d=Dlist.GetNext(posD);
		p.x=((t.GetHour()*60+t.GetMinute())*60+t.GetSecond())*m_unitX+m_origion.x;
		p.y=m_origion.y-(d*m_unitY);
		for(int i=0;i<cou;i++)
		{
			m_dc.MoveTo(p);
			t=Tlist.GetNext(posT);
			d=Dlist.GetNext(posD);
			span=t-ot;
			ot=t;
			if(span.GetTotalSeconds()>60)
			{
				p.y=m_origion.y;
				m_dc.LineTo(p);
				p.x=((t.GetHour()*60+t.GetMinute())*60+t.GetSecond())*m_unitX+m_origion.x;
				m_dc.LineTo(p);
			}
			p.x=((t.GetHour()*60+t.GetMinute())*60+t.GetSecond())*m_unitX+m_origion.x;
			p.y=m_origion.y-(d*m_unitY);
			m_dc.LineTo(p);
		}
	}
}
//获得点
void CChartControl::GetPoints(CTime time, double var)
{
	Tlist.AddTail(time);
	
	Dlist.AddTail(var);
}

CTime CChartControl::StrToTime(CString timeStr)
{
	int nYear,nMonth,nDay,nHour,nMinute,nSecond;
	CTime time=CTime::GetCurrentTime();
	nYear=time.GetYear();
	nMonth=time.GetMonth();
	nDay=time.GetDay();
	sscanf(timeStr.Left(2),"%d", &nHour);// 得到时
	sscanf(timeStr.Mid(3,2), "%d", &nMinute); // 得到分
	sscanf(timeStr.Mid(6,2), "%d", &nSecond); // 得到秒
	
	time=CTime(nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return time;
}

CString CChartControl::TimeToStr(CTime time)
{
	CString str;
	str.Format("%.2d:%.2d:%.2d",time.GetHour(),time.GetMinute(),time.GetSecond());
	return str;
}
