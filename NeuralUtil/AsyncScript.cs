using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace NeuralUtil
{
    public class AsyncScript : MonoBehaviour
    {
        public void PerformTaskAsync(IEnumerator task)
        {
            StartCoroutine(DoTaskThenDie(task));
        }
        IEnumerator DoTaskThenDie(IEnumerator task)
        {
            yield return task;
            Destroy(gameObject);
        }
    }
}