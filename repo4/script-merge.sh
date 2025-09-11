#!/bin/bash

# Lista de repositórios antigos (nome do remote + URL)
repos=(
  "repo1 git@github.com:GarthTeixeira/treinamentosOpenGl.git"
  "repo2 git@github.com:GarthTeixeira/simulacaoAFD.git"
  "repo3 git@github.com:GarthTeixeira/serieDeTaylorComParalelismo.git"
  "repo4 git@github.com:GarthTeixeira/crivoDeEratostenesComParalelismo.git"
  "repo5 git@github.com:GarthTeixeira/encontrarMaioresNumerosComMPI.git"
  "repo7 git@github.com:GarthTeixeira/AnalisadorSintaticoLexico.git"
  "repo8 git@github.com:GarthTeixeira/BinaryTreeExperiment.git"
  "repo8 git@github.com:GarthTeixeira/AHP_Practices.git"
)

for repo in "${repos[@]}"; do
  echo "Separa nome e URL"
  remote_name=$(echo $repo | awk '{print $1}')
  remote_url=$(echo $repo | awk '{print $2}')

  echo "Processando $remote_name..."

  echo "Adiciona remote temporário"
  git remote add "$remote_name" "$remote_url"
  git fetch "$remote_name"

  echo "Cria branch temporária a partir do histórico do repo"
  git checkout -b "${remote_name}-branch" "$remote_name/main" 2>/dev/null || git checkout -b "${remote_name}-branch" "$remote_name/master"

  echo "Cria subpasta e move arquivos"
  mkdir -p "$remote_name"
  git ls-tree --name-only -r HEAD | xargs -I files mv files "$remote_name/" 2>/dev/null || true
  git add .
  git commit -m "Move $remote_name para subpasta"

  echo "Volta para main do mega-repo e faz merge"
  git checkout master
  git merge "${remote_name}-branch" --allow-unrelated-histories -m "Merge $remote_name no mega-repo"

  echo "Remove remote temporário"
  git remote remove "$remote_name"

  echo "Deleta branch temporária"
  git branch -D "${remote_name}-branch"
done

echo "Todos os repositórios foram mesclados no mega-repo!"
