
#ifndef MUIU8G2_HH
#define MUIU8G2_HH

#include "mui.h"
#include "mui_u8g2.h"

class MUIU8G2
{
  protected:
    mui_t mui;
  public:
    MUIU8G2(void) { }
  
    MUIU8G2(U8G2 &u8g2, fds_t *fds, muif_t *muif_list, size_t muif_cnt) {
      mui_Init(&mui, (void *)u8g2.getU8g2(), fds, muif_list, muif_cnt);
    }
    void begin(U8G2 &u8g2, fds_t *fds, muif_t *muif_list, size_t muif_cnt) {
      mui_Init(&mui, (void *)u8g2.getU8g2(), fds, muif_list, muif_cnt);
    }
    mui_t *getMUI(void) { return &mui; }

    uint8_t getCurrentCursorFocusPosition(void) { return mui_GetCurrentCursorFocusPosition(&mui); }
    
    int getCurrentFormId(void) { return mui_GetCurrentFormId(&mui); }

    
    void draw(void) { mui_Draw(&mui); }
    //void getSelectableFieldTextOption(fds_t *fds, uint8_t nth_token)
    //  { mui_GetSelectableFieldTextOption(&mui, fds, nth_token); }      
    void enterForm(fds_t *fds, uint8_t initial_cursor_position) { mui_EnterForm(&mui, fds, initial_cursor_position); }
    void leaveForm(void) { mui_LeaveForm(&mui); }
    uint8_t gotoForm(uint8_t form_id, uint8_t initial_cursor_position) { return mui_GotoForm(&mui, form_id, initial_cursor_position); }
    
    void saveForm(void) { mui_SaveForm(&mui); }
    void restoreForm(void) { mui_RestoreForm(&mui); }
    void nextField(void) { mui_NextField(&mui); }
    void prevField(void) { mui_PrevField(&mui); }
    void sendSelect(void) { mui_SendSelect(&mui); }
    
    void sendSelectWithExecuteOnSelectFieldSearch(void) { mui_SendSelectWithExecuteOnSelectFieldSearch(&mui); }
    
    
    int isFormActive(void) { return mui_IsFormActive(&mui); }    
};


#endif /* MUIU8G2_HH */
