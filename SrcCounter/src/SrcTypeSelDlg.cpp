
#include "wx_pch.h"
#include "SrcTypeSelDlg.h"

#ifndef WX_PRECOMP
//(*InternalHeadersPCH(SrcTypeSelDlg)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#endif

//(*InternalHeaders(SrcTypeSelDlg)
//*)


/* Source types number */
const int N_SRC_TYPE_NUM = 25;

/* Source type */
const wxChar* CSZ_SRC_TYPES[N_SRC_TYPE_NUM] =
{
    // CppCounter
    _T(".cpp"), // 1
    _T(".cxx"), // 2
    _T(".c"),
    _T(".h"),
    _T(".rc"),  // 5
    _T(".tlh"), // 6
    _T(".tli"),
    _T(".java"),
    _T(".cs"),

    // JspCounter
    _T(".aspx"),    // 10
    _T(".asp"),     // 11
    _T(".php"),     // 12
    _T(".php3"),    // 13
    _T(".jsp"),		// 14

    // TxtCounter
    _T(".htm"),		// 15
    _T(".html"),	// 16


	// BasCounter
    _T(".vb"),		// 17
    _T(".bas"),		// 18
    _T(".frm"),
    _T(".ctl"),		// 20
    _T(".cls"),

	// PasCounter
    _T(".pas"), // 22
    _T(".dfm"), // 23

    // TODO: SqlCounter
    _T(".sql"), // 24

    _T(".txt"), // 25

};

//(*IdInit(SrcTypeSelDlg)
const long SrcTypeSelDlg::ID_STATICTEXT1 = wxNewId();
const long SrcTypeSelDlg::ID_CHECKLISTBOX1 = wxNewId();
const long SrcTypeSelDlg::ID_CHECKBOX1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SrcTypeSelDlg,wxDialog)
    //(*EventTable(SrcTypeSelDlg)
    //*)
END_EVENT_TABLE()

SrcTypeSelDlg::SrcTypeSelDlg(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
    //(*Initialize(SrcTypeSelDlg)
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;
    
    Create(parent, wxID_ANY, _("Select types dialog"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("&Select source file types for counting:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer1->Add(StaticText1, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_lbxSrcTypes = new wxCheckListBox(this, ID_CHECKLISTBOX1, wxDefaultPosition, wxSize(180,200), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
    BoxSizer1->Add(m_lbxSrcTypes, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_ckbSelAll = new wxCheckBox(this, ID_CHECKBOX1, _("Select &all file types"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    m_ckbSelAll->SetValue(false);
    BoxSizer1->Add(m_ckbSelAll, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    m_btnOk = new wxButton(this, wxID_OK, _("&Ok"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
    BoxSizer2->Add(m_btnOk, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_btnCancel = new wxButton(this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
    BoxSizer2->Add(m_btnCancel, 2, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);
    Center();
    
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&SrcTypeSelDlg::Onm_ckbSelAllClick);
    Connect(wxID_OK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SrcTypeSelDlg::OnBtnOkClick);
    Connect(wxID_CANCEL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SrcTypeSelDlg::OnBtnCancelClick);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&SrcTypeSelDlg::OnInit);
    //*)
}

SrcTypeSelDlg::~SrcTypeSelDlg()
{
    //(*Destroy(SrcTypeSelDlg)
    //*)
}

void SrcTypeSelDlg::OnInit(wxInitDialogEvent& event)
{
    //
    for (int i = 0; i < N_SRC_TYPE_NUM; i++)
    {
        m_lbxSrcTypes->Append(CSZ_SRC_TYPES[i]);
    }
}

void SrcTypeSelDlg::SetSrcTypes(wxString strSrcTypes)
{
    m_strSrcTypes = strSrcTypes;
}

void SrcTypeSelDlg::OnBtnOkClick(wxCommandEvent& event)
{
    // Get checked item list
    int nNum = m_lbxSrcTypes->GetCount();

    wxString strTemp;
    for (int i = 0; i < nNum; i++)
    {
        //
        if (m_lbxSrcTypes->IsChecked(i))
        {
            strTemp = m_lbxSrcTypes->GetString(i);
            // strcpy();
            m_strSrcTypes =  m_strSrcTypes + strTemp + _T(";");
        }
    }

    EndModal(wxID_OK);
}

void SrcTypeSelDlg::OnBtnCancelClick(wxCommandEvent& event)
{
	EndModal(wxID_CANCEL);
}

void SrcTypeSelDlg::Onm_ckbSelAllClick(wxCommandEvent& event)
{
    bool bChecked = m_ckbSelAll->IsChecked();
    int nNum = m_lbxSrcTypes->GetCount();

    for (int i = 0; i < nNum; i++)
    {
        m_lbxSrcTypes->Check(i, bChecked);
    }
}