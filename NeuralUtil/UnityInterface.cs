using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace NeuralUtil
{
    public static class UnityInterface
    {
        public static void PerformTaskAsync(IEnumerator task)
        {
            GameObject g = new GameObject();
            AsyncScript ass = g.AddComponent<AsyncScript>();
            ass.PerformTaskAsync(task);
        }
        public static void ReloadScene()
        {
            PerformTaskAsync(loadscene());
        }
        static IEnumerator loadscene()
        {
            //if (AbstractPlayerControl.GetInstance(Player.ONE) is AIPlayer)
            //{
            //    Genome g = (AbstractPlayerControl.GetInstance(Player.ONE) as AIPlayer).Brain;
            //    //g.SaveGenome("LastGenome");
            //    AddGenome(g);
            //    if (prevmaxscore.Key != maxscore.Key)
            //    {
            //        GetMax(false).SerialiseObject("LastGenome");
            //        //GetMax(false).SaveGenome("LastGenome");
            //        SetPrevScore();
            //    }
            //}
            yield return new WaitForSeconds(0.1f);
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex, LoadSceneMode.Single);
        }
        public static void NormaliseVec3(this Vector3 pos, out double x, out double y, out double z, double minx, double maxx,double miny, double maxy, double minz, double maxz)
        {
            x = Formatting.Normalise(pos.x, minx, maxx);
            y = Formatting.Normalise(pos.y, miny, maxy);
            z = Formatting.Normalise(pos.z, minz, maxz);
        }

        /// <summary>
        /// This won't work in a library, will remember to find a workaround..
        /// </summary>
        public static void Quit()
        {
            #if UNITY_EDITOR
                UnityEditor.EditorApplication.isPlaying = false; 
            #else
                Application.Quit();
            #endif
        }

    }
}