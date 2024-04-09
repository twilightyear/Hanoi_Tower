#include </Users/twilightyear/Desktop/Coding/Cpp/STD/std_lib_facilities.h>

// 하노이의 탑 출력
void PrintTowers(const vector<vector<int>>& hanoi) {
    for (int i = 0; i < hanoi.size(); i++) {
        cout << '[' << i + 1 << "] ";
        for (int j = 0; j < hanoi[i].size(); j++) {
            cout << hanoi[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}

// 움직임이 가능한지
int IsMoveAllowed(const vector<vector<int>>& hanoi, int from, int to, int tower_count) {
    int last_value_to, last_value_from, none_zero_from_count = 0, none_zero_to_count = 0;

    // 주어진 번호 인덱스화
    from--;
    to--;

    // 사용할 타워들의 인덱스가 타워의 개수 범위 안의 정수여야 함
    if ((from >= 0 && from < tower_count) && (to >= 0 && to < tower_count)) {

        // 움직일 타워의 크기 확인
        for (int k = 0; k < hanoi[from].size(); k++) {
            if (hanoi[from][k] != 0) {
                none_zero_from_count++;
            }
        }

        // 타겟 타워의 크기 확인
        for (int k = 0; k < hanoi[to].size(); k++) {
            if (hanoi[to][k] != 0) {
                none_zero_to_count++;
            }
        }

        // 움직일 타워의 크기가 1 이상일 것
        if (none_zero_from_count > 0) {
            // 타겟 타워가 비어 있거나, 가장 위의 디스크가 현재 타워의 가장 위의 디스크보다 큰 경우에만 이동 가능합니다.
            if (none_zero_to_count == 0 || hanoi[to].back() > hanoi[from].back()) {
                return 1; // 이동 가능
            } else {
                return 0; // 이동 불가능
            }
        } else {
            return 0; // 이동 불가능
        }
    } else {
        return 0; // 이동 불가능
    }
}

// 실질적 움직임 시도
void MoveDisk(vector<vector<int>>& hanoi, int from, int to) {
    int from_value = hanoi[from - 1].back(); 

    // 움직일 탑의 가장 마지막에 있는 값 삭제
    hanoi[from - 1].pop_back();

    // 옮길 탑의 가장 마지막 부분에 변수에 저장된 값 추가
    hanoi[to - 1].push_back(from_value);
}

// 초기화 함수
void Initialize(vector<vector<int>>& hanoi, int size, int tower_count) {
    // 하노이의 탑 첫 탑에 모든 디스크들 추가
    for (int i = 0; i < size; i++) {
        hanoi[0].push_back(size - i); 
    }
}

// 인터페이스 출력
void PrintLine(int turn_count, int tower_count) {
    cout << '[' << turn_count << "] " << "From which tower will you move a disk to which tower? (from=[";
    for (int i = 0; i < tower_count; i++) {
        if (i != tower_count - 1) {
            cout << i + 1 << '|';
        } else {
            cout << i + 1;
        }
    }
    cout << "], to=[";

    for (int i = 0; i < tower_count; i++) {
        if (i != tower_count - 1) {
            cout << i + 1 << '|';
        } else {
            cout << i + 1;
        }
    }
    cout << "]):";
}

// 하노이 탑이 완성되었는지 확인하는 함수
int IsHanoiComplete(const vector<vector<int>>& hanoi, int size, int tower_count) {
    // 마지막 타워에 디스크가 있고, 올바른 순서로 쌓여 있는지 확인
    for (int i = 0; i < hanoi[tower_count - 1].size(); i++) {
        if (hanoi[tower_count - 1][i] != size - i) {
            return 1;
        }
    }
    // 나머지 타워가 비어 있는지 확인
    for (int i = 0; i < tower_count - 1; i++) {
        if (!hanoi[i].empty()) {
            return 1;
        }
    }
    return 0;
}

// 메인함수
int main() {
    // 턴 횟수 초기화
    int turn_count = 1;

    // 사용자 입력을 위한 값 초기화
    int from, to;

    // 하노이탑 타워의 개수
    int tower_count = 3;

    int running = 1;

    vector<vector<int>> hanoi(tower_count); 

    int size;
    cout << "Hi! Please select number of disks you wish to use: ";
    cin >> size;

    // 초기화 함수 호출
    Initialize(hanoi, size, tower_count);

    // 메인 루프
    while (running) {
        if (!IsHanoiComplete(hanoi, size, tower_count)) {
            char input;
            cout << "Congratulation! You solved it in " << turn_count - 1 << " moves!" << endl;
            cout << "Do you want to play it again? (Y/N): ";
            cin >> input;

            if (input == 'Y' || input == 'y') {
                cout << "Hi! Please select number of disks you wish to use: ";
                cin >> size;
                turn_count = 1;
                hanoi.clear(); 
                hanoi.resize(tower_count); 
                Initialize(hanoi, size, tower_count);
            } else if (input == 'N' || input == 'n') {
                running = 0;
                break;
            } else {
                cout << "Error" << endl;
                break;
            }
        }

        // 타워 상태 출력
        PrintTowers(hanoi);

        // 사용자 입력 받기 위한 인터페이스 출력
        PrintLine(turn_count, tower_count);

        // 사용자 입력
        cin >> from >> to;

        // 움직임 가능한지 체크 : 가능하다면
        if (IsMoveAllowed(hanoi, from, to, tower_count)) {
            // 성공 문 출력
            cout << "=> Move succeeded!" << endl;
            // 실질적 이동
            MoveDisk(hanoi, from, to);
        } else {
            // 실패 문 출력
            cout << "=> Move failed!" << endl;
        }

        // 턴 횟수 추가
        turn_count++;
    }

    // 프로그램 종료
    return 0;
}
