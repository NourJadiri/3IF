echo "Test ID;Return code validation;Out result;StdErr result;File creation result;Global result" >results.csv
nOk=0
nKo=0
nTotal=0
nMis=0

for i in Test*
do
  # gestion des cas particuliers (commande -g)
  # il faut notamment supprimer les .dot qui ont ete generes
  # mais aussi retrouver les anciens contenus des fichiers qui doivent servir pour tester
  # lorsqu'un fichier non vide est donné sur la ligne de commande
  # (et donc verifier si on ecrase bien le contenu ou pas)
  if [ $i -eq 8 ] || [ $i -eq 9 ] || [ $i -eq 17 ] || [ $i -eq 23 ] || [ $i -eq 25 ]
  then
    rm -f shortTest.dot
  elif [ $i -eq 11 ] || [ $i -eq 13 ]
  then
    cp shortTest_Old.dot shortTest.dot
  elif [ $i -eq 12 ]
  then
      cp dontTouchTest_old.dot dontTouchTest.old
      rm -f touchTest.dot
  fi

  ./test.sh $i results.csv

  result=$?
  if [ $result -eq 0 ]
  then
    let "nKo=$nKo+1"
  elif [ $result -eq 1 ]
  then
    let "nOk=$nOk+1"
  else
    let "nMis=$nMis+1"
  fi
  let "nTotal=$nTotal+1"
done

echo "Passed tests     : $nOk"
echo "Failed tests     : $nKo"
echo "Misformed tests  : $nMis"
echo "-----------------------"
echo "Total            : $nTotal"
