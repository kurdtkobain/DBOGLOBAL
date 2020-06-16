using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Reflection; // For Missing.Value and BindingFlags
using System.Runtime.InteropServices; // For COMException
using Excel = Microsoft.Office.Interop.Excel;

namespace MiHaeng4
{
    class ThreadTask
    {
        private int rowStart;   // ó�� �����ϴ� ��
        private int rowCnt;     // �� ī��Ʈ
        private int rowInc;     // �����ϴ� ��
        private Excel.Range rng;
        private CTextDataBase dataBase;
        private static Object thisLock = new Object();

        public ThreadTask(int rowStart, int rowCnt, int rowInc)
        {
            this.rowStart = rowStart;
            this.rowCnt = rowCnt;
            this.rowInc = rowInc;
        }

        public ThreadTask(CTextDataBase dataBase, int rowStart, int rowCnt, int rowInc, Excel.Range rng)
        {
            this.dataBase = dataBase;
            this.rowStart = rowStart;
            this.rowCnt = rowCnt;
            this.rowInc = rowInc;
            this.rng = rng;
        }

        // TextAllData�� �о �ʿ� �����Ѵ�.
        public void InsertTextAllData()
        {
            string row;
            for(int i = rowStart; i < rowCnt; i += rowInc)
            {
                row = i.ToString();

                TextAllDataTable.InsertMap("N", row, "npc");
                TextAllDataTable.InsertMap("L", row, "mob");
                TextAllDataTable.InsertMap("X", row, "object");
                TextAllDataTable.InsertMap("V", row, "place");
                TextAllDataTable.InsertMap("H", row, "item");
                TextAllDataTable.InsertMap("Z", row, "questItem");
                TextAllDataTable.InsertMap("P", row, "skill");
                TextAllDataTable.InsertMap("AB", row, "etc");

                MH4Global.pgbXLS.Value = Math.Min(MH4Global.pgbXLS.Maximum, MH4Global.pgbXLS.Value + 1);
                if(MH4Global.pgbXLS.Value == MH4Global.pgbXLS.Maximum)
                {
                    MH4Global.lbXLS.Text = "Load Text All Table Complete!";
                    MH4Global.lbXLS.Update();

                    MH4Global.mainForm.OnLoadedTextAllData();
                }

                Thread.Sleep(0);
            }
        }

        public void LoadXLS()
        {
            Excel.Range rngVal;
            int nCount = 0;

            CTextData[] data = new CTextData[MH4Global.colList.Length * (rowCnt + 1) / MH4Global.THREAD_MAX];
            for (int i = 0; i < data.Length; ++i)
            {
                data[i] = new CTextData();
            }

            StringBuilder sbText = new StringBuilder();
            sbText.Capacity = 1024;
            StringBuilder sbPreFix = new StringBuilder();
            StringBuilder sbID = new StringBuilder();

            for (int i = rowStart; i < rowCnt; i += rowInc)
            {
                sbPreFix.Remove(0, sbPreFix.Length);

                MH4Global.pgbXLS.Value = Math.Min(MH4Global.pgbXLS.Maximum, MH4Global.pgbXLS.Value + 1);
                rngVal = (Excel.Range)rng.Cells[i, 2];  // ID�� Prefix                                                
                if (rngVal.Value2 == null)
                    continue;

                sbPreFix.Append(rngVal.Value2.ToString());                

                for (int j = 1; j < MH4Global.colList.Length; ++j)
                {
                    sbID.Remove(0, sbID.Length);
                    sbText.Remove(0, sbText.Length);

                    sbID.Append(sbPreFix.ToString());                                        
                    sbID.Append(j >= 10 ? j.ToString() : "0" + j.ToString());                                                            

                    rngVal = (Excel.Range)rng.Cells[i, MH4Global.colList[j]];
                    if (rngVal.Value2 == null) // ���ڿ��� ������ @
                    {
                        sbText.Append("@");
                    }
                    else // �����̽��� �ִ� ��쵵 �ִ�. �� ��쵵 @ó��
                    {
                        sbText.Append(rngVal.Value2.ToString().TrimStart(' '));
                        if(sbText.Length > 0)
                        {
                            sbText.Insert(0, GetMetaTag(i, MH4Global.colList[j]));
                        }
                        else
                        {
                            sbText.Append("@");
                        }                        
                    }

                    data[nCount].Id = sbID.ToString();
                    data[nCount].Text = sbText.ToString();

                    lock(thisLock)
                    {
                        dataBase.AddData(data[nCount]);
                    }
                    
                    ++nCount;
                }

                Thread.Sleep(0);
            }
        }

        // Special Quest �� XLS�� �ε��Ѵ�. (�Ϲ� ����Ʈ ������ ������ �ٸ���)
        public void LoadXLSSpecial()
        {
            Excel.Range rngVal1, rngVal2;
            int nCount = 0;

            CTextData[] data = new CTextData[MH4Global.colList.Length * (rowCnt + 1) / MH4Global.THREAD_MAX];
            for (int i = 0; i < data.Length; ++i)
            {
                data[i] = new CTextData();
            }

            StringBuilder sbText = new StringBuilder();
            sbText.Capacity = 1024;            
            StringBuilder sbID = new StringBuilder();

            for (int i = rowStart; i < rowCnt; i += rowInc)
            {
                sbID.Remove(0, sbID.Length);
                sbText.Remove(0, sbText.Length);

                MH4Global.pgbXLS.Value = Math.Min(MH4Global.pgbXLS.Maximum, MH4Global.pgbXLS.Value + 1);

                // ID               
                rngVal1 = (Excel.Range)rng.Cells[i, 2];
                if (rngVal1.Value2 == null)
                    continue;

                sbID.Append(rngVal1.Value2.ToString());

                // �ؽ�Ʈ ���ڿ� ( C �� + H ��)                
                rngVal1 = rng.get_Range("C" + i.ToString(), Missing.Value);
                rngVal2 = rng.get_Range("H" + i.ToString(), Missing.Value);
                
                if(rngVal1.Value2 != null)
                {
                    sbText.Append(rngVal1.Value2.ToString());
                }
                
                if(rngVal2.Value2 != null)
                {
                    sbText.Append(rngVal2.Value2.ToString());
                }
                
                if(sbText.Length == 0)
                {
                    sbText.Append("@");
                }
                
                data[nCount].Id = sbID.ToString();
                data[nCount].Text = sbText.ToString();

                lock (thisLock)
                {
                    dataBase.AddData(data[nCount]);
                }
                
                ++nCount;                

                Thread.Sleep(0);
            }
        }

        // ��Ÿ �±� ���� col�� �°� ��ȯ�Ѵ�.
        private string GetMetaTag(int row, int col)
        {
            StringBuilder sbRet = new StringBuilder("[metatag = ");
            if (col < 147)
            {
                sbRet.Append("5]");                
            }
            else
            {
                int tagCol = col + 31;
                Excel.Range rngTag = (Excel.Range)rng.Cells[row, tagCol];
                if (rngTag.Value2 == null)
                {
                    sbRet.Append("7]");
                }
                else
                {
                    // �����̽��� �ִ� ��쵵 �ִ�. 
                    string tag = rngTag.Value2.ToString();
                    tag = tag.TrimStart(' ');
                    if(tag.Length > 0)
                    {
                        sbRet.Append(tag);
                        sbRet.Append("]");
                    }
                    else
                    {
                        sbRet.Append("7]");
                    }                    
                }
            }

            return sbRet.ToString();
        } 
    }
}
