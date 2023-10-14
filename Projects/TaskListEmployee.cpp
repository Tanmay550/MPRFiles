#include <fmx.h>
#pragma hdrstop
#include "TaskListEmployee.h"
#include "LoginForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TTaskList *TaskList;
//---------------------------------------------------------------------------
__fastcall TTaskList::TTaskList(TComponent* Owner)
	: TForm(Owner)
{

}

void TTaskList::SetUsername(const AnsiString& username)
{
	FUsername = username; // Assign the username to the class field
}

//---------------------------------------------------------------------------



void __fastcall TTaskList::RetrieveAndDisplayTasks()
{
    // Check if a username is set
    if (FUsername.IsEmpty())
    {
        ShowMessage("Username not set. Cannot retrieve tasks.");
        return;
    }
    // Assuming you have a TFDQuery component named FDQuery1
    FDQuery1->SQL->Clear();
	FDQuery1->SQL->Add("SELECT Tasks FROM Employee WHERE username = :username");
    FDQuery1->ParamByName("username")->AsString = FUsername; // Set the username parameter
    try
    {
        FDQuery1->Open(); // Execute the query
        // Display the tasks in the TEdit component
        AnsiString tasksText = "";
        while (!FDQuery1->Eof)
        {
            tasksText += FDQuery1->FieldByName("Tasks")->AsString + "\r\n";
            FDQuery1->Next();
        }
		ListBox->Items->Add(tasksText);
        ShowMessage("Retrieved Tasks: \n" + tasksText);
    }
    catch (Exception &e)
    {
        ShowMessage("Error: " + e.Message);
    }

		FDQuery1->Close(); // Close the query
}


void __fastcall TTaskList::LogoutButtonClick(TObject *Sender)
{
   this->Hide();
   Login->Show();
}



void __fastcall TTaskList::AddTaskButtonClick(TObject *Sender)
{
	String taskText = AddTaskEdit->Text;
	ListBox->Items->Add(taskText);
	AddTaskEdit->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TTaskList::ListBoxItemClick(TCustomListBox * const Sender, TListBoxItem * const Item)

{
	int index = Item->Index;
	UnicodeString selectedItemText = ListBox->Items->Strings[ListBox->ItemIndex];
	ListBox->Items->Delete(index);
	ListComp->Items->Add(selectedItemText);
}
//---------------------------------------------------------------------------


