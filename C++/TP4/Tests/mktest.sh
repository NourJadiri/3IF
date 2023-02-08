echo "Test ID;Return code validation;Out result;StdErr result;File creation result;Global result" >results.csv
nOk=0
nKo=0
nTotal=0
nMis=0

for i in Test*
do
  # gestion des cas particuliers (commande -g)
  # il faut notamment retrouver les anciens contenus des fichiers qui doivent servir pour tester
  # lorsqu'un fichier non vide est donné sur la ligne de commande
  # (et donc verifier si on ecrase bien le contenu ou pas)

  test_num=${i#Test} # pour caster le numero du test en int

  if [ $test_num -eq 11 ] || [ $test_num -eq 13 ]
  then
    cp $i/shortTest_Old.dot $i/shortTest.dot
  elif [ $test_num -eq 12 ]
  then
    cp $i/dontTouchTest_old.dot $i/dontTouchTest.dot
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
