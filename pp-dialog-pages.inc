/*
    PawnPlus Dialog Pages
    Author: Kanaru Yuuki
    Versiao: 1.0.0

    PawnPlus Dialog Pages is the include that make the listing dialog easier
    by utilising `list` system, we can make such feature with ease.

    Functions:
      native AddDialogListitem(playerid, const string[], {Float, _}:...);
      native AddDialogListitemStr(playerid, StringTag:string);
      native Task:ShowPlayerDialogPages(playerid, DIALOG_STYLE:style, const title[], items_per_page, const button1[], const button2[] = "", const prevButton[] = "<<<<", const nextButton[] = ">>>>");

    Credits:
      IS4Code (IllidanS4) - PawnPlus creator which i love it.
      AmirAhmady (iAmir) - Providing corrected format `#emit`.
      Nick (Nickk888SAMP) - The creator of ndialog-pages.inc which i took the inspiration from.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#if defined _inc_pp_dialog_pages
    #undef _inc_pp_dialog_pages
#endif

#if defined _pp_dialog_pages_included
    #endinput
#endif

#define _pp_dialog_pages_included

#include <PawnPlus>

#if !defined async_dialogs_included
enum e_DIALOG_RESPONSE_INFO
{
    E_DIALOG_RESPONSE_Response,
    E_DIALOG_RESPONSE_Listitem,
    E_DIALOG_RESPONSE_InputText[128 + 1],
}
#endif

#if !defined PAWN_PLUS_DIALOG_PAGES_ID
    const PAWN_PLUS_DIALOG_PAGES_ID = 12609;
#endif

#if !defined DIALOG_PAGE_BUFFER_SIZE
    #define DIALOG_PAGE_BUFFER_SIZE 1024
#endif

#if !defined DIALOG_PAGE_HEADER_SIZE
    #define DIALOG_PAGE_HEADER_SIZE 64
#endif

#if !defined DIALOG_PAGE_BUTTON_SIZE
    #define DIALOG_PAGE_BUTTON_SIZE 64
#endif

#if defined DIALOG_NO_NATIVE_CALL
    native ShowPlayerDialog__s(playerid, dialogid, style, const caption[], ConstAmxString:info, const button1[], const button2[]) = ShowPlayerDialog;
#endif

// Thanks easyDialog.inc
#if !defined _INC_open_mp
    #if !defined DIALOG_STYLE
        #define DIALOG_STYLE: _:
    #endif
#endif


new 
    List:gPlayerList[MAX_PLAYERS],
    DIALOG_STYLE:gPlayerStyles[MAX_PLAYERS],
    gPlayerPage[MAX_PLAYERS],
    gPlayerItemsPerPage[MAX_PLAYERS],
    Task:gPlayerTasks[MAX_PLAYERS];

static 
    gPlayerTitle[MAX_PLAYERS][DIALOG_PAGE_HEADER_SIZE],
    gPlayerHeaders[MAX_PLAYERS][DIALOG_PAGE_HEADER_SIZE],
    gPlayerPrevBtn[MAX_PLAYERS][DIALOG_PAGE_BUTTON_SIZE],
    gPlayerNextBtn[MAX_PLAYERS][DIALOG_PAGE_BUTTON_SIZE],
    gPlayerBtn1[MAX_PLAYERS][DIALOG_PAGE_BUTTON_SIZE],
    gPlayerBtn2[MAX_PLAYERS][DIALOG_PAGE_BUTTON_SIZE];

stock AddDialogListitem(playerid, const string[], {Float, _}:...)
{
    const static_args = 2;
    const args_diff = (3 - static_args) * 4;

    static args;
    args = numargs();

    static str[DIALOG_PAGE_BUFFER_SIZE];
    const str_size = sizeof(str);

    if (args > static_args)
    {

        while (--args >= static_args)
        {
            #emit LCTRL 5
            #emit LOAD.alt args
            #emit SHL.C.alt 2
            #emit ADD.C 12
            #emit ADD
            #emit LOAD.I
            #emit PUSH.pri
        }

        #emit PUSH.S string
        #emit PUSH.C str_size
        #emit PUSH.C str
        #emit LOAD.S.pri 8
        #emit ADD.C args_diff
        #emit PUSH.pri
        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        if (!list_valid(gPlayerList[playerid])) gPlayerList[playerid] = list_new();
        list_add_str_s(gPlayerList[playerid], str_replace(str_new(str), "\n", ""));
        return 1;
    }

    if (!list_valid(gPlayerList[playerid])) gPlayerList[playerid] = list_new();
    list_add_str_s(gPlayerList[playerid], str_replace(str_new(string), "\n", ""));
    return 1;
}

stock AddDialogListitemStr(playerid, ConstStringTag:string)
{
    string = str_replace(string, "\n", "");
    if (!list_valid(gPlayerList[playerid])) gPlayerList[playerid] = list_new();
    list_add_str_s(gPlayerList[playerid], string);
}

stock Task:ShowPlayerDialogPages(playerid, DIALOG_STYLE:style, const title[], items_per_page, const button1[], const button2[] = "", const prevButton[] = "<<<<", const nextButton[] = ">>>>")
{
    InvokeDialogPages(playerid, style, title, items_per_page, button1, button2, prevButton, nextButton);

    if(task_valid(gPlayerTasks[playerid])) task_delete(gPlayerTasks[playerid]);
    gPlayerTasks[playerid] = task_new();
    return gPlayerTasks[playerid];
}

static stock InvokeDialogPages(playerid, DIALOG_STYLE:style, const title[], items_per_page, const button1[], const button2[] = "", const prevButton[] = "<<<<", const nextButton[] = ">>>>")
{
    CleanupDialogPages(playerid);

    if (!list_valid(gPlayerList[playerid])) return ShowPlayerDialog(playerid, PAWN_PLUS_DIALOG_PAGES_ID, style, title, "", button1, button2);

    gPlayerItemsPerPage[playerid] = items_per_page;
    gPlayerPage[playerid] = 0;
    gPlayerStyles[playerid] = style;

    format(gPlayerTitle[playerid], sizeof(gPlayerTitle), title);

    if (style == DIALOG_STYLE_TABLIST_HEADERS)
    {
        list_get_str(gPlayerList[playerid], 0, gPlayerHeaders[playerid], 128);
        list_remove_deep(gPlayerList[playerid], 0);
    }

    format(gPlayerPrevBtn[playerid], 128, prevButton);
    format(gPlayerNextBtn[playerid], 128, nextButton);
    format(gPlayerBtn1[playerid], 128, button1);
    format(gPlayerBtn2[playerid], 128, button2);

    ShowDialogPages(playerid, 0);
    return 1;
}

static stock ShowDialogPages(playerid, page)
{
    new
        List:list = gPlayerList[playerid],
        items_per_page = gPlayerItemsPerPage[playerid],
        total_items = list_size(list),
        total_pages = (total_items + items_per_page - 1) / items_per_page;

    // Validate page number
    if (page < 0) page = 0;
    if (page >= total_pages && total_pages > 0) page = total_pages - 1;
    gPlayerPage[playerid] = page;

    new
        start = page * items_per_page,
        end = min((page + 1) * items_per_page, total_items),
        String:content = str_new_static("");

    //  Add dialog header
    if (gPlayerStyles[playerid] == DIALOG_STYLE_TABLIST_HEADERS)
    {
        content = str_format("%s\n", gPlayerHeaders[playerid]);
    }

    // Add items for current page
    for (new i = start; i < end; i++)
    {
        str_append_format(content, "%S\n", list_get_str_s(list, i));
    }

    // Add navigation buttons if needed
    if (page < total_pages - 1)
        str_append_format(content, "%s\n", gPlayerNextBtn[playerid]);

    if (page > 0)
        str_append_format(content, "%s\n", gPlayerPrevBtn[playerid]);

    // Call dialog
#if defined DIALOG_NO_NATIVE_CALL
    return ShowPlayerDialog__s(playerid, PAWN_PLUS_DIALOG_PAGES_ID, gPlayerStyles[playerid], gPlayerTitle[playerid], content, gPlayerBtn1[playerid], gPlayerBtn2[playerid]);
#else
    return pawn_call_native("ShowPlayerDialog", "iiisSss", playerid, PAWN_PLUS_DIALOG_PAGES_ID, gPlayerStyles[playerid], gPlayerTitle[playerid], content, gPlayerBtn1[playerid], gPlayerBtn2[playerid]);
#endif
}

static stock CleanupDialogPages(playerid)
{
    gPlayerTitle[playerid][0] = 0;
    gPlayerHeaders[playerid][0] = 0;
    gPlayerPrevBtn[playerid][0] = 0;
    gPlayerNextBtn[playerid][0] = 0;
    gPlayerBtn1[playerid][0] = 0;
    gPlayerBtn2[playerid][0] = 0;
    return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    if (dialogid == PAWN_PLUS_DIALOG_PAGES_ID)
    {
        // Sanitize inputs.
        for (new i = 0, l = strlen(inputtext); i < l; i ++)
        {
            if (inputtext[i] == '%')
            {
                inputtext[i] = '#';
            }
        }

        if (!response)
        {
            new dialog_response[e_DIALOG_RESPONSE_INFO];
            dialog_response[E_DIALOG_RESPONSE_Response] = response;
            dialog_response[E_DIALOG_RESPONSE_Listitem] = listitem;
            strcat(dialog_response[E_DIALOG_RESPONSE_InputText], inputtext, 129);

            CleanupDialogPages(playerid);

            if (list_valid(gPlayerList[playerid]))
            {
                list_delete_deep(gPlayerList[playerid]);
                gPlayerList[playerid] = INVALID_LIST;
            }

            new Task:task = gPlayerTasks[playerid];
            gPlayerTasks[playerid] = Task:0;
            task_set_result_arr(task, dialog_response);
            return 1;
        }

        new
            List:list = gPlayerList[playerid],
            page = gPlayerPage[playerid],
            items_per_page = gPlayerItemsPerPage[playerid],
            total_items = list_size(list),
            total_pages = (total_items + items_per_page - 1) / items_per_page,
            start = page * items_per_page,
            end = min((page + 1) * items_per_page, total_items),
            page_item_count = end - start,
            bool:has_next = (page < total_pages - 1),
            bool:has_prev = (page > 0),
            next_index = page_item_count,
            prev_index = next_index + (has_next ? 1 : 0);

        if (has_next && listitem == next_index)
        {
            ShowDialogPages(playerid, page + 1);
            return 1;
        }
        else if (has_prev && listitem == prev_index)
        {
            ShowDialogPages(playerid, page - 1);
            return 1;
        }

        // Calculate actual item index in the original list
        new actual_index = start + listitem;

        new dialog_response[e_DIALOG_RESPONSE_INFO];
        dialog_response[E_DIALOG_RESPONSE_Response] = 1;
        dialog_response[E_DIALOG_RESPONSE_Listitem] = actual_index;
        strcat(dialog_response[E_DIALOG_RESPONSE_InputText], inputtext, 129);

        CleanupDialogPages(playerid);

        if (list_valid(gPlayerList[playerid]))
        {
            list_delete_deep(gPlayerList[playerid]);
            gPlayerList[playerid] = INVALID_LIST;
        }

        new Task:task = gPlayerTasks[playerid];
        gPlayerTasks[playerid] = Task:0;
        task_set_result_arr(task, dialog_response);
        return 1;
    }

#if defined PDP_OnDialogResponse
    return PDP_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
#else
    return 0;
#endif
}

public OnPlayerDisconnect(playerid, reason)
{
    CleanupDialogPages(playerid);

    if (list_valid(gPlayerList[playerid]))
    {
        list_delete_deep(gPlayerList[playerid]);
        gPlayerList[playerid] = INVALID_LIST;
    }

#if defined PDP_OnPlayerDisconnect
    return PDP_OnPlayerDisconnect(playerid, reason);
#else
    return 1;
#endif
}

#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif

#define OnDialogResponse PDP_OnDialogResponse
#if defined PDP_OnDialogResponse
    forward PDP_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif

#define OnPlayerDisconnect PDP_OnPlayerDisconnect
#if defined PDP_OnPlayerDisconnect
    forward PDP_OnPlayerDisconnect(playerid, reason);
#endif
