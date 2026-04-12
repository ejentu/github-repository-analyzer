import requests
import json
import sys


def getUserRepos(username):
    url = f"https://api.github.com/users/{username}/repos"
    response = requests.get(url)

    if response.status_code == 200:
        repos = response.json()
        if not repos:
            return None

        repo_isimleri = [repo['name'] for repo in repos]

        return repo_isimleri

    else:
        print("Kullanıcı Bulunamadı")
        return None

#stats = {
#"name" : secilenRepo.get("name"),
#"stars" : secilenRepo.get("stargazers_count"),
#"forks" : secilenRepo.get("forks_count"),
#"open_issues" : secilenRepo.get("open_issues_count"),
#"size" : secilenRepo.get("size"),
#"language" : secilenRepo.get("language")
#}

def getRepoDetails(username, repo):

    url = f"https://api.github.com/repos/{username}/{repo}"
    response = requests.get(url)
    if response.status_code == 200:
        repo = response.json()
        if not repo:
            return None

        stats = {
            "name": repo.get("name"),
            "stars": repo.get("stargazers_count"),
            "forks": repo.get("forks_count"),
            "open_issues": repo.get("open_issues_count"),
            "size": repo.get("size"),
            "language": repo.get("language")
        }

        return stats
    return None


if len(sys.argv) == 3: # program + user + repo
    user = sys.argv[1]
    repo_name = sys.argv[2]
    data = getRepoDetails(user, repo_name)
    dosya_adi = "repo.data.json"
elif len(sys.argv) == 2: # program + user
    user = sys.argv[1]
    data = getUserRepos(user)
    dosya_adi = "repo.name.data.json"
else:
    print("Hatalı parametre sayısı!")
    sys.exit(1)

if data:
    # Tam yolu C++ ile aynı yap
    tam_yol = f"C:/Users/esoyu/PycharmProjects/githubApi/{dosya_adi}"
    with open(tam_yol, "w") as f:
        json.dump(data, f, indent=4)

