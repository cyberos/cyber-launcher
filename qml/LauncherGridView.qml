import QtQuick 2.0
import org.cyber.launcher 1.0

PagedGrid {
    id: gridView

    property alias query: appsProxyModel.filterPattern
    property int cellSize: 130
    property int sideMargins: root.width * 0.1
    property int itemSize: root.height * 0.17

//    rows: 4
//    columns: 6

    rows: (root.height - root.height * 0.2) / itemSize
    columns: (root.width - sideMargins * 2) / itemSize

    width: columns * itemSize
    height: rows * itemSize

    model: SortFilterProxyModel {
        id: appsProxyModel
        sourceModel: applicationManager
        filterRoleName: "filterInfo"
        filterCaseSensitivity: Qt.CaseInsensitive
        isSortLocaleAware: true
        sortCaseSensitivity: Qt.CaseSensitive
        sortOrder: Qt.AscendingOrder
        sortRoleName: "name"
    }

    delegate: Item {
        width: gridView.itemSize
        height: width

        LauncherGridDelegate {
            id: delegate

            anchors {
                fill: parent
                margins: 10
            }
        }
    }
}
