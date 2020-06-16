using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection; // For Missing.Value and BindingFlags
using System.Runtime.InteropServices; // For COMException
using Excel = Microsoft.Office.Interop.Excel;
using System.Windows.Forms;
using System.Threading;

namespace MiHaeng4
{
    class ConvertXLS
    {
        // �Ϻ��� ���̺��� �±׸� �о�ͼ� �����ϰ�, �ٽ� XLS�� �����Ѵ�.
        public bool ConvertTagXLS(string fileName, LocalizeSource localize)
        {
            string nakedFileName = System.IO.Path.GetFileName(fileName);
            Excel.Application app = new Excel.Application();
            app.Workbooks.Open(fileName, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value,
                               Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value, Missing.Value);

            Excel.Workbook workBook = app.Workbooks[1];
            workBook.Activate();
            Excel.Worksheet sheet = (Excel.Worksheet)workBook.Sheets[1];

            Excel.Range rng;
            MH4Global.pgbXLS.Minimum = 2;
            MH4Global.pgbXLS.Maximum = sheet.UsedRange.Rows.Count + 1;
            MH4Global.lbXLS.Text = "Load and Convert to Japan XLS... : " + nakedFileName;
            MH4Global.lbXLS.Update();

            
            if(MH4Global.IsSpecialQuestXLS(fileName))   // ����� ����Ʈ ����
            {
                for (int i = 2; i < sheet.UsedRange.Rows.Count + 1; ++i)
                {                    
                    rng = sheet.UsedRange.get_Range("C" + i.ToString(), Missing.Value);
                    if (rng.Value2 != null)
                    {
                        ReplaceTag(rng, localize);
                    }

                    rng = sheet.UsedRange.get_Range("H" + i.ToString(), Missing.Value);
                    if(rng.Value2 != null)
                    {
                        ReplaceTag(rng, localize);
                    }
                    
                    MH4Global.pgbXLS.Value = i;   // ���α׷����ٴ� ������� ǥ���Ѵ�.
                }

            }
            else // �Ϲ� ����Ʈ ����
            {
                for (int i = 2; i < sheet.UsedRange.Rows.Count + 1; ++i)
                {
                    for (int j = 1; j < MH4Global.colList.Length; ++j)
                    {
                        rng = (Excel.Range)sheet.UsedRange.Cells[i, MH4Global.colList[j]];

                        if (rng.Value2 != null)
                        {
                            ReplaceTag(rng, localize);
                        }
                    }

                    MH4Global.pgbXLS.Value = i;   // ���α׷����ٴ� ������� ǥ���Ѵ�.
                }
            }

            app.ActiveWorkbook.Close(true, Missing.Value, Missing.Value);
            MH4Global.lbXLS.Text = "Load & Convert to XLS Complete : " + nakedFileName;
            MH4Global.lbXLS.Update();
            return true;
        }

        void ReplaceTag(Excel.Range rng, LocalizeSource localize)
        {
            char[] splitChar = { '[', ']' };
            StringBuilder sbText = new StringBuilder();
            StringBuilder sbOrg = new StringBuilder();
            StringBuilder sbNew = new StringBuilder();
            string text = null;

            // �����̽��� �ִ� ��쵵 �ִ�. �� ��쵵 @ó��
            text = rng.Value2.ToString();
            text = text.TrimStart(' ');
            if (text != "")
            {
                sbText.Length = 0;
                sbText.Append(text);

                string[] words = text.Split(splitChar);
                string strConvertText = null;
                for (int k = 1; k < words.Length; k = k + 2)
                {
                    if (words[k] == "user" || words[k] == "class" || words[k] == "race" || words[k] == "br")
                        continue;

                    // Text All Data���� ID�� �˻��Ѵ�.                          
                    if (localize == LocalizeSource.LOCAL_KOREAN)
                    {
                        strConvertText = TextAllDataTable.ConvertTag(words[k]);
                    }
                    else if (localize == LocalizeSource.LOCAL_JAPANESE)
                    {
                        strConvertText = TextAllDataTable.ConvertJapanText(words[k]);
                    }

                    if (strConvertText != null)
                    {
                        sbOrg.Length = 0;
                        sbNew.Length = 0;

                        sbOrg.Append("[");
                        sbOrg.Append(words[k]);
                        sbOrg.Append("]");

                        sbNew.Append("[");
                        sbNew.Append(strConvertText);
                        sbNew.Append("]");

                        sbText.Replace(sbOrg.ToString(), sbNew.ToString());
                    }
                }

                rng.Value2 = sbText.ToString();
            }
        }
    }
}
